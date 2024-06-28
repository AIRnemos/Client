import { Dispatch } from "react"
import { Actions, AllActions, Data, Step } from ".."
import { CardContent, CardDescription, CardHeader, CardTitle } from "@/components/ui/card"
import { Label } from "@/components/ui/label"
import { Input } from "@/components/ui/input"

function Component({data, dispatch}: {data: Data, dispatch: Dispatch<AllActions>}) {
    return <>
    <CardHeader>
        <CardTitle>Name</CardTitle>
        <CardDescription>TODO</CardDescription>
    </CardHeader>
    <CardContent>
        <div className="grid gap-4">
            <div className="grid gap-2">
                <Label htmlFor="ssid">SSID</Label>
                <Input
                    id="ssid"
                    type="text"
                    placeholder={"AIRnemos - " + AIRNEMOS_NAME}
                    required

                    onChange={(event) => dispatch({type: Actions.WIFI_AP, ssid: event.target.value})}
                    value={data.wifi_ap.ssid}
                />
            </div>
            <div className="grid gap-2">
                <Label htmlFor="password">Password</Label>
                <Input
                    id="password"
                    type="text"
                    required

                    onChange={(event) => dispatch({type: Actions.WIFI_AP, password: event.target.value})}
                    value={data.wifi_ap.password}
                />
            </div>
        </div>
    </CardContent>
</>
}

export const WifiAP: Step = {
    component: (data: Data, dispatch: Dispatch<AllActions>) => <Component data={data} dispatch={dispatch}></Component>,
    next: (index: number) => index + 4,
    previos: (index: number) => index - 1,
    canNext: (data: Data) =>    data.wifi_ap != null && 
                                data.wifi_ap.ssid != null && 
                                data.wifi_ap.ssid.length > 0 && 
                                data.wifi_ap.ssid.length <= 32 && 
                                data.wifi_ap.password != null &&
                                data.wifi_ap.password.length >= 8 &&
                                data.wifi_ap.password.length <= 64
}