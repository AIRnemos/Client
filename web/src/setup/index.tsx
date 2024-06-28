import { Button } from "@/components/ui/button"
import {
  Card,
  CardFooter,
} from "@/components/ui/card"
import { Welcome } from "./steps/0-welcome"
import { Dispatch, Reducer, useReducer, useState } from "react"
import { Name } from "./steps/1-name";
import { Wifi } from "./steps/2-wifi";
import { WifiAP } from "./steps/21-wifi-ap";
import { WifiSearch } from "./steps/22-wifi-search";
import { WifiPassword } from "./steps/221-wifi-password";
import { WifiTest } from "./steps/222-wifi-test";
import { Check } from "./steps/3-check";
import { Done } from "./steps/4-done";
import { WifisProvider } from "./provider/wifis";

export type Step = {
    component: (data: Data, dispatch: Dispatch<AllActions>, next: () => void, previos: () => void) => JSX.Element,
    next: (index: number, data: Data) => number,
    previos: (index: number, data: Data) => number,
    canNext?: (data: Data) => boolean,
    hideNext?: boolean
    hidePrevios?: boolean
    nextText?: string
}

export enum WifiMode {
    NONE = "NONE",
    WIFI = "WIFI",
    AP = "AP"
}

export type Data = {
    name: string
    wifi: WifiMode
    wifi_ap: {
        ssid: string,
        password: string
    },
    wifi_data: {
        ssid: string,
        password: string,

        secure?: boolean,
        ip?: string
    }
}

export enum Actions {
    NAME,
    WIFI_MODE,
    WIFI_AP,
    WIFI
}

export type AllActions = NameAction | WiFiModeAction | WiFiAction

type NameAction = {
    type: Actions.NAME,
    name: string
}
type WiFiModeAction = {
    type: Actions.WIFI_MODE,
    mode: WifiMode
}
type WiFiAction = {
    type: Actions.WIFI_AP | Actions.WIFI,
    ssid?: string,
    password?: string
    secure?: boolean
    ip?: string
}

export function Setup() {
    const [index, setIndex] = useState(0);
    const [data, dispatch] = useReducer<Reducer<Data, AllActions>>(
        (state: Data, action: AllActions) => {
            switch (action.type) {
                case Actions.NAME:
                    return {...state, name: action.name }
                case Actions.WIFI_MODE:
                    return {...state, wifi: action.mode }
                case Actions.WIFI_AP:
                case Actions.WIFI:
                    let dataObj = action.type == Actions.WIFI ? state.wifi_data : state.wifi_ap
                    if (action.ssid != null) 
                        dataObj = { ...dataObj, ssid: action.ssid }
                    if (action.password != null) 
                        dataObj = { ...dataObj, password: action.password }
                    if (action.secure != null && action.type == Actions.WIFI) 
                        // @ts-ignore
                        dataObj = { ...dataObj, secure: action.secure }
                    if (action.ip != null && action.type == Actions.WIFI) 
                        // @ts-ignore
                        dataObj = { ...dataObj, ip: action.ip }
                    return action.type == Actions.WIFI ? {...state, wifi_data: dataObj } : {...state, wifi_ap: dataObj }
            }
        },
        {
            name: AIRNEMOS_NAME,
            wifi: WifiMode.WIFI,
            wifi_ap: {
                ssid: "AIRnemos - " + AIRNEMOS_NAME,
                password: ""
            },
            wifi_data: {
                ssid: "",
                password: "",
                secure: false
            }
        }
    )

    const steps: Step[] = [
        Welcome,
        Name,
        Wifi,
        WifiAP,
        WifiSearch,
        WifiPassword,
        WifiTest,
        Check,
        Done
    ]

    function next() {
        setIndex(steps[index].next(index, data))
    }

    function previos() {
        setIndex(steps[index].previos(index, data))
    }

    const hideSpacer = !steps[index].hideNext && !steps[index].hidePrevios
    return (
        <WifisProvider>
            <div className="contents sm:flex items-center justify-center h-screen w-screen">
                <Card className="contents sm:flex flex-col mx-auto w-[24rem] min-h-[24rem]">
                    { steps[index].component(data, dispatch, next, previos) }
                    {hideSpacer &&
                        <span className="flex-grow"></span>
                    }
                    <CardFooter className="fixed left-0 right-0 bottom-0 sm:static flex gap-2">
                        {!steps[index].hidePrevios &&
                            <Button onClick={previos}>Zurück</Button>
                        }
                        { !steps[index].hideNext &&
                            <Button 
                                className="flex-grow"
                                onClick={next}
                                disabled={steps[index].canNext != undefined && !steps[index].canNext(data)}
                            >{ steps[index].nextText ?? "Weiter"}</Button>
                        }
                    </CardFooter>
                </Card>
            </div>
        </WifisProvider>
    ) 
}