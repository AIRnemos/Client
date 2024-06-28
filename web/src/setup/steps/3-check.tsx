import { CardContent, CardDescription, CardHeader, CardTitle } from "@/components/ui/card"
import { Data, Step, WifiMode } from ".."

function Component({ data }: { data: Data}) {
    return <>
        <CardHeader>
            <CardTitle>Fast geschaft! 🤩</CardTitle>
            <CardDescription>Nur noch ein Letztes mal überprüfen!</CardDescription>
        </CardHeader>
        <CardContent>
            <p>Name: {data.name}</p>
            <p>Wlan: {data.wifi == WifiMode.WIFI ? data.wifi_data.ssid : data.wifi == WifiMode.AP ? "AP (eigenes Wlan)" : "Nicht" }</p>
            {data.wifi == WifiMode.AP && <>
                <p>SSID: {data.wifi_ap.ssid}</p>
                <p>Password: {data.wifi_ap.password}</p>
            </>}
            {data.wifi != WifiMode.NONE && <p>IP: http://{data.wifi == WifiMode.AP ? "192.168.1.1" : data.wifi_data.ip ?? data.name + ".local" }/</p>}
        </CardContent>
    </>
}

export const Check: Step = {
    component: (data: Data) => <Component data={data}></Component>,
    next: (index: number) => index + 1,
    previos: (index: number, data: Data) => {
        if (data.wifi == WifiMode.NONE) return index - 5
        if (data.wifi == WifiMode.AP) return index - 4
        return index - 3
    },
    nextText: "Bestätigen"
}