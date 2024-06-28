import { useContext } from "react";
import { WiFisContext } from "../provider/wifis";

export function useBlockWifi() {
    return useContext(WiFisContext).setBlocked
}