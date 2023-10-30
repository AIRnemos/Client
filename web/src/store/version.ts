import {get, writable} from "svelte/store"

export const newest = writable<string | undefined>(undefined)

export const check = async  () => {
    const res = await fetch("https://updateserver.airnemos.de/latest")

    if(res.status != 200) 
        throw new Error("wrong code", {
            cause: res
        })

    newest.set(await res.text())
}