import { useContext } from "react";
import { WiFisContext, Wifi } from "../provider/wifis";

export function useWifs(): [Wifi[], boolean] {
    const data = useContext(WiFisContext)
    return [data.wifis, data.loading]
}