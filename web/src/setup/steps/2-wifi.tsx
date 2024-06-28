import { CardContent, CardDescription, CardHeader, CardTitle } from "@/components/ui/card";
import { Label } from "@/components/ui/label";
import { Actions, AllActions, Data, Step, WifiMode } from "..";
import { Dispatch } from "react";
import { Select, SelectContent, SelectItem, SelectTrigger, SelectValue } from "@/components/ui/select";

function Component({data, dispatch}: {data: Data, dispatch: Dispatch<AllActions>}) {
    return <>
        <CardHeader>
            <CardTitle>Wlan</CardTitle>
            <CardDescription>TODO {data.wifi}</CardDescription>
        </CardHeader>
        <CardContent>
            <div className="grid gap-4">
                <div className="grid gap-2">
                    <Label htmlFor="wifi-mode">Mode</Label>
                    <Select onValueChange={(value: string) => dispatch({ type: Actions.WIFI_MODE, mode: value as WifiMode})} defaultValue={data.wifi}>
                        <SelectTrigger id="mode">
                            <SelectValue />
                        </SelectTrigger>
                        <SelectContent>
                            <SelectItem value={WifiMode.WIFI}>WiFi / Wlan</SelectItem>
                            <SelectItem value={WifiMode.AP}>AP (eigenes Wlan)</SelectItem>
                            <SelectItem value={WifiMode.NONE}>Nichts</SelectItem>
                        </SelectContent>
                    </Select>
                </div>
            </div>
        </CardContent>
    </>
}

export const Wifi: Step = {
    component: (data: Data, dispatch: Dispatch<AllActions>) => <Component data={data} dispatch={dispatch}></Component>,
    next: (index: number, data: Data) => {
        if (data.wifi == WifiMode.NONE) return index + 5
        if (data.wifi == WifiMode.WIFI) return index + 2
        return index + 1
    },
    previos: (index: number) => index - 1,
    canNext: (data: Data) => data.wifi != null
}