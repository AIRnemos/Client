import { AlertCircle, Loader2 } from "lucide-react"
import { Actions, AllActions, Data, Step } from ".."
import { CardDescription, CardTitle } from "@/components/ui/card"
import { useBlockWifi } from "../hook/block"
import { Dispatch, useEffect, useState } from "react"
import { APIClient } from "@/lib/api"
import { Button } from "@/components/ui/button"

function Component({ data, dispatch, next, previos }: { data: Data, next: () => void, previos: () => void, dispatch: Dispatch<AllActions>}) {
    const [error, setError] = useState(false)

    const block = useBlockWifi()

    useEffect(() => {
        const check = async () => {
            block(true)

            try {
                const result = await APIClient.url("/wifi/check").post({
                    ssid: data.wifi_data.ssid,
                    password: data.wifi_data.password
                }) as {success: boolean, ip: string}
    
    
                if(!result.success) throw "not connected"
    
                dispatch({ type: Actions.WIFI, ip: result.ip})
                
                next()
            } catch (err) {
                setError(true)
            }
    
            block(false)
        }

        check()
    }, [])

    return <div className="flex flex-col gap-4 items-center justify-center w-full flex-grow pt-80 sm:pt-0">
        {!error ? <>
            <Loader2 className="animate-spin" size="60px" />
            <CardTitle>Verbinde mit {data.wifi_data.ssid}</CardTitle>
        </> : <>
            <AlertCircle />
            <CardTitle>Fehler</CardTitle>
            <CardDescription>
            Verbindung mit {data.wifi_data.ssid} fehlgeschlagen!
            </CardDescription>
            <Button onClick={previos}>Nochmal probieren!</Button>
        </>
        }
        
    </div>
}

export const WifiTest: Step = {
    component: (data: Data, dispatch: Dispatch<AllActions>, next: () => void, previos: () => void) => <Component data={data} next={next} dispatch={dispatch} previos={previos}></Component>,
    next: (index: number) => index + 1,
    previos: (index: number) => index - 1,
    canNext: (data: Data) => data.name != null && data.name.length > 0,
    hidePrevios: true,
    hideNext: true
}