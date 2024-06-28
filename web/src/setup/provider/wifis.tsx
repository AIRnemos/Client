import { APIClient } from "@/lib/api";
import { Dispatch, PropsWithChildren, SetStateAction, createContext, useEffect, useRef, useState } from "react";

export type Wifi = {
    ssid: string
    rssi: number,
    secure: boolean
}

export const WiFisContext = createContext<{
    wifis: Wifi[],
    setBlocked: (blocked: boolean) => void,
    loading: boolean
}>({ wifis: [], setBlocked: () => {}, loading: false })

let running: Promise<void>
let timer: number

async function loadWiFis(
    setData: Dispatch<SetStateAction<Wifi[]>>, 
    blocked: () => boolean, 
    setLoading: Dispatch<SetStateAction<boolean>>
) {
    if (running != null) return running;

    async function inner() {
        if(!blocked()) {
            setLoading(true)
            try {
                const data = await APIClient.get("/wifi/scan") as Wifi[]
    
                setData(
                    data.sort((a: Wifi, b: Wifi) => b.rssi - a.rssi)
                )
            } catch (err) {
            } finally {
                setLoading(false)
            }
        }
        setTimeout(loadWiFis, blocked() ? 500 : 10000)
    }

    running = inner()
}

export function WifisProvider({ children }: PropsWithChildren) {
    const [data, setData] = useState<Wifi[]>([])

    const [blocked, setBlocked] = useState<boolean>(false)
    const blockRef = useRef<boolean>(blocked);
    blockRef.current = blocked

    const [loading, setLoading] = useState<boolean>(false)

    useEffect(() => {
        loadWiFis(setData, () => blockRef.current, setLoading)        

        return () => {
            if (running != null) {
                running.then(() => window.clearTimeout(timer))
            } else
                window.clearTimeout(timer)
        }
    }, [])

    return (
        <WiFisContext.Provider value={{loading, setBlocked, wifis: data}}>
            {children}
        </WiFisContext.Provider>
    )
} 