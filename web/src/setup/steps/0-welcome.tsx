import { CardContent, CardHeader, CardTitle } from "@/components/ui/card";
import { Step } from "..";

function Component() {
    return <>
        <CardHeader>
            <CardTitle>Hallo 👋</CardTitle>
        </CardHeader>
        <CardContent>
            <p>Vielen Dank für den Kauf unserer CO₂-Ampel! Wir freuen uns sehr, dass Sie sich für unser Produkt entschieden haben und sind sicher, dass es Ihnen dabei helfen wird, die Luftqualität in Ihrem Raumlichkeiten im Blick zu behalten.</p>
            <br />
            <p>Nun müssen Sie nur noch den Einrichtungsassistenten abzuschließen.</p>
        </CardContent>
    </>
}

export const Welcome: Step = {
    component: () => <Component></Component>,
    next: (index: number) => index + 1,
    previos: (index: number) => index,
    hidePrevios: true
}