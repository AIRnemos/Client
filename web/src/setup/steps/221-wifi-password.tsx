import { CardContent, CardDescription, CardHeader, CardTitle } from "@/components/ui/card"
import { Actions, AllActions, Data, Step } from ".."
import { Input } from "@/components/ui/input"
import { Label } from "@/components/ui/label"
import { Dispatch, useState } from "react"

function Component({data, dispatch}: {data: Data, dispatch: Dispatch<AllActions>}) {
    const [password, setPassword] = useState("");
    const [password2, setPassword2] = useState("");

    return <>
        <CardHeader>
            <CardTitle>Password für {data.wifi_data.ssid}</CardTitle>
            <CardDescription>TODO</CardDescription>
        </CardHeader>
        <CardContent>
            <div className="grid gap-4">
                <div className="grid gap-2">
                    <Label htmlFor="password">Password</Label>
                    <Input
                        id="password"
                        type="password"
                        required

                        onChange={(event) => {
                            setPassword(event.target.value)
                            dispatch({type: Actions.WIFI, password: event.target.value == password2 ? event.target.value : ""})
                        }}
                        value={password}
                    />
                </div>

                <div className="grid gap-2">
                    <Label htmlFor="password2">Password wiederholen</Label>
                    <Input
                        id="password2"
                        type="password"
                        required

                        onChange={(event) => {
                            setPassword2(event.target.value)
                            dispatch({type: Actions.WIFI, password: event.target.value == password ? event.target.value : ""})
                        }}
                        value={password2}
                    />
                </div>
            </div>
        </CardContent>
    </>
}

export const WifiPassword: Step = {
    component: (data: Data, dispatch: Dispatch<AllActions>) => <Component data={data} dispatch={dispatch}></Component>,
    next: (index: number) => index + 1,
    previos: (index: number) => index - 1,
    canNext: (data: Data) =>    data.wifi_data != null && 
                                data.wifi_data.password != null && 
                                data.wifi_data.password.length >= 8 && 
                                data.wifi_data.password.length <= 64
}