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

export const newest = writable<string | undefined>(undefined)

export const check = async  () => {
    /*const res = await fetch("https://updateserver.airnemos.de/latest")

    if(res.status != 200) 
        throw new Error("wrong code", {
            cause: res
        })

    newest.set(await res.text())*/
    throw new Error("Not Implemented")
}