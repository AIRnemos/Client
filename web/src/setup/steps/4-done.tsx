import { AlertCircle, Loader2 } from "lucide-react"
import { Data, Step, WifiMode } from ".."
import { CardDescription, CardTitle } from "@/components/ui/card"
import { Button } from "@/components/ui/button"
import { useBlockWifi } from "../hook/block"
import { useEffect, useState } from "react"
import { APIClient } from "@/lib/api"

function Component({ data, previos }: { data: Data, previos: () => void}) {
    const [error, setError] = useState(false)
    const [success, setSuccess] = useState(false)

    const block = useBlockWifi()

    useEffect(() => {
        const check = async () => {
            block(true)
            setError(false)

            try {

                await APIClient.url("/setup").post({
                    name: data.name,
                    password: "",
                    buzzer: true,
                    wifi: {
                        mode: data.wifi == WifiMode.NONE ? 0 : data.wifi == WifiMode.AP ? 1 : 2,
                        ssid: data.wifi == WifiMode.WIFI ? data.wifi_data.ssid : data.wifi == WifiMode.AP ? data.wifi_ap.ssid : undefined,
                        password: data.wifi == WifiMode.WIFI ? data.wifi_data.password : data.wifi == WifiMode.AP ? data.wifi_ap.password : undefined,
                        retires: -20,
        
                        fallback: {
                            mode: 1,
                            ssid: "AIRnemos - " + data.name,
                            password: "",
                            retires: -1,
                        }
                    },
                })
                
                setSuccess(true)
            } catch (err) {
                setError(true)
                setSuccess(false)
            }
    
            block(false)
        }

        check()
    }, [])

    let inner;
    if(error) {
        inner = <>
            <AlertCircle />
            <CardTitle>Fehler</CardTitle>
            <CardDescription>
                Einrichten fehlgeschlagen!
            </CardDescription>
            <Button onClick={previos}>Nochmal probieren!</Button>
        </>
    } else if(success) {
        inner = <>
            <CardTitle>Geschaft! 🥳</CardTitle>
        </>
    } else {
        inner = <>
            <Loader2 className="animate-spin" size="60px" />
            <CardTitle>Richte Ampel ein...</CardTitle>
        </>
    }

    return <div className="flex flex-col gap-4 items-center justify-center w-full flex-grow pt-80 sm:pt-0">
        { inner }
    </div>
}

export const Done: Step = {
    component: (data: Data, _, __, previos: () => void, ) => <Component data={data} previos={previos}></Component>,
    next: (index: number) => index + 1,
    previos: (index: number) => index - 1,
    canNext: (data: Data) => data.name != null && data.name.length > 0,
    hideNext: true,
    hidePrevios: true
}