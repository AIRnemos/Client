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
import {get, writable} from "svelte/store";
import { APIClient } from "../lib/api";

export const canNext = writable(true)
export const triggerNext = writable(false)
export const triggerBack = writable(false)

export const loadingWiFis = writable(false)
export const loadingWiFisError = writable(undefined)
export const blockSearch = writable(false)
export const wifis = writable([])

async function loadWiFis() {
    if(!get(blockSearch)) {
        loadingWiFis.set(true)
        try {
            const data = await APIClient.get<any[] | any>("/wifi/scan")

            if (data?.success == false) {
                loadingWiFisError.set("0000-0001-00000")
                loadingWiFis.set(false)
                return
            }

            wifis.set(data.sort((a, b) => a - b))
            loadingWiFis.set(false)
            loadingWiFisError.set(undefined)
        } catch (err) {
            loadingWiFisError.set("0001-0001-10001")
            loadingWiFis.set(false)
        }
    }

    setTimeout(loadWiFis, get(blockSearch) ? 500 : 10000)
}
loadWiFis()