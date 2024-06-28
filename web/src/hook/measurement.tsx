import { useContext } from "react";
import { MeasurementContext, Measurements } from "../provider/measurement";

export function useMeasurement(): Measurements {
    return useContext(MeasurementContext)
}