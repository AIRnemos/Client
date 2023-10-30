import {get, writable} from "svelte/store"
import { APIClient } from "../lib/api"
import { wait } from "../lib/utils";

export const current = writable({
    co2: 0,
    temp: 0,
    hum: 0,
    err: false
})

export const history = writable<{value: number, date: Date}[]>(null)

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