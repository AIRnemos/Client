/*
    AIRnemos is a software for CO2 meter.
    Copyright (C) 2023 Quentin Schuster

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <https://www.gnu.org/licenses/>.
*/
import {get, writable} from "svelte/store"
import { APIClient } from "../lib/api"
import { wait } from "../lib/utils";

export const current = writable({
    co2: 0,
    temp: 0,
    hum: 0,
    err: false
})

export const history = writable<{value: number, date: Date}[]>([])

let timer;
async function init() {
    try {
        const data = await APIClient.get("/measurement/history");
    
        const date = new Date();
        let labels = []
        for (let i = 0; i < data.co2.length; i++) {
            labels.push(new Date(date.getTime()));
            date.setSeconds(date.getSeconds() - 5);
        }

        const co2Data: {value: number, date: Date}[] = []
        for (let i = 0; i < labels.length; i++) {
            const time = labels[i]
            co2Data.push({date: time, value: Math.round(data.co2[i])})
        }

        history.set(co2Data);
    } catch (error) {
        await wait(2000);
        return init()
    }

    timer = setTimeout(read, 5000)
}

async function read() {
    try {
        const data = await APIClient.get("/measurement")

        const formatted = {
            co2: Math.round(data.co2),
            temp: Math.round(data.temp),
            hum: Math.round(data.hum),
            err: false
        }

        current.set(formatted);
    } catch (error) {
        current.set({
            co2: 0,
            temp: 0,
            hum: 0,
            err: true
        });
    }

    history.update(data => {
        data.unshift({value: get(current).co2, date: new Date()})
        data.pop()

        return data
    })
    
    timer = setTimeout(read, 5000)
}

export const loader = init()