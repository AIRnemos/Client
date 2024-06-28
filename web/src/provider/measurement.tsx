import { PropsWithChildren, Reducer, createContext, useEffect, useReducer } from "react";
import { APIClient } from "../lib/api";

export type Measurements = {
    co2: number;
    temp: number;
    hum: number;
    error: boolean;
    history: { co2: number; temp: number; hum: number; date: Date; }[];
}

export const MeasurementContext = createContext<Measurements>({
    co2: 0,
    temp: 0,
    hum: 0,
    error: false,
    history: []
})

type ReducerActionInit = {
    type: "INIT",
    data: Measurements
}

type ReducerActionUpdate = {
    type: "UPDATE",
    co2: number,
    temp: number,
    hum: number,
    error: boolean,
}

let initPromise: Promise<void>
let timer: number;
function init(dispatch: React.Dispatch<ReducerActionInit | ReducerActionUpdate>) {
    
    if (initPromise == null) {
        async function _init() {
            try {
                const data = await APIClient.get("/measurement/history") as { co2: number[], temp: number[], hum: number[] };
            
                const date = new Date();
                let labels = []
                for (let i = 0; i < data.co2.length; i++) {
                    labels.push(new Date(date.getTime()));
                    date.setSeconds(date.getSeconds() - 5);
                }
        
                const co2Data: {co2: number, temp: number, hum: number, date: Date}[] = []
                for (let i = 0; i < labels.length; i++) {
                    const time = labels[i]
                    co2Data.push({date: time, co2: Math.round(data.co2[i]), hum: Math.round(data.hum[i]), temp: Math.round(data.temp[i])})
                }
        
                dispatch({type: "INIT", data: {co2: Math.round(data.co2[0]), hum: Math.round(data.hum[0]), temp: Math.round(data.temp[0]), history: co2Data.reverse(), error: false}});
            } catch (error) {
                dispatch({type: "INIT", data: {co2: 0, hum: 0, temp: 0, history: [], error: true}});
                await new Promise(res => setTimeout(res, 2000));
        
                return await _init()
            }
        }

        initPromise = _init()
    }

    return initPromise
}

async function read(dispatch: React.Dispatch<ReducerActionInit | ReducerActionUpdate>) {
    let newData: Measurements

    try {
        const data = await APIClient.get("/measurement") as { co2: number, temp: number, hum: number}

        newData = {
            co2: Math.round(data.co2),
            temp: Math.round(data.temp),
            hum: Math.round(data.hum),
            error: false,
            history: []
        }
    } catch (error) {
        newData = {
            co2: 0,
            temp: 0,
            hum: 0,
            error: true,
            history: []
        }
    }

    dispatch({ type: "UPDATE", ...newData})
    
    if (timer != null) {
        clearTimeout(timer)
    }
    timer = window.setTimeout(read, 5000, dispatch)
}

export function MeasurementProvider({ children }: PropsWithChildren) {
    const [data, dispatch] = useReducer<Reducer<Measurements, ReducerActionInit | ReducerActionUpdate>>((state, action) => {
        if (action.type == "INIT") {
            return action.data
        } else if (action.type == "UPDATE"){
            const history = state.history

            history.push({co2: action.co2, hum: action.hum, temp: action.temp, date: new Date()})
            history.shift()

            return {
                co2: action.co2,
                temp: action.temp,
                hum: action.hum,
                error: action.error,
                history
            }
        }
        return state
    }, {
        co2: 0,
        temp: 0,
        hum: 0,
        error: false,
        history: []
    })

    useEffect(() => {
        init(dispatch)
            .then(() => {
                if (timer != null) {
                    clearTimeout(timer)
                }
            
                timer = window.setTimeout(read, 5000, dispatch)
            })

        return () => {
            window.clearTimeout(timer)
        }
    }, [])

    return (
        <MeasurementContext.Provider value={data}>
            {children}
        </MeasurementContext.Provider>
    )
} 