
import { CardContent, CardDescription, CardHeader, CardTitle } from "@/components/ui/card"
import { Actions, AllActions, Data, Step } from ".."
import { useWifs } from "../hook/wifis"
import { Loader2, Lock, Unlock, WifiIcon } from "lucide-react"
import { Dispatch } from "react"

function Component({ dispatch, next }: { dispatch: Dispatch<AllActions>, next: () => void }) {
    const [wifis, loading] = useWifs()
    return <>
        <CardHeader>
            <CardTitle>Netzwerke</CardTitle>
            <CardDescription>
                Wähle ein Netzwerk aus. { loading && <Loader2 className="inline animate-spin" />}
            </CardDescription>
        </CardHeader>
        <CardContent>
            {
                wifis.map((wifi) => <div 
                    className="mb-1 p-2 flex gap-2 items-center justify-items-center rounded hover:bg-primary-foreground cursor-pointer"
                    onClick={ () => { dispatch({ type: Actions.WIFI, ssid: wifi.ssid, secure: wifi.secure }); next() }}
                    key={wifi.ssid}
                    >
                    <WifiIcon size="20px" />
                    { wifi.ssid }
                    <span className="flex-grow" />
                    { wifi.secure ? <Lock size="16px" /> : <Unlock size="16px" /> }
                </div>)
            }
        </CardContent>
    </>
}

export const WifiSearch: Step = {
    component: (_: Data, dispatch: Dispatch<AllActions>, next: () => void) => <Component dispatch={dispatch} next={next}></Component>,
    next: (index: number) => index + 1,
    previos: (index: number) => index - 2,
    canNext: (data: Data) => data.wifi_data != null && data.wifi_data.ssid != null && data.wifi_data.ssid.length > 0,
    hideNext: true
}