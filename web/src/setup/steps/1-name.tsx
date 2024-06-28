import { CardContent, CardDescription, CardHeader, CardTitle } from "@/components/ui/card";
import { Input } from "@/components/ui/input";
import { Label } from "@/components/ui/label";
import { Actions, AllActions, Data, Step } from "..";
import { Dispatch } from "react";

function Component({data, dispatch}: {data: Data, dispatch: Dispatch<AllActions>}) {
    return <>
        <CardHeader>
            <CardTitle>Name</CardTitle>
            <CardDescription>TODO</CardDescription>
        </CardHeader>
        <CardContent>
            <div className="grid gap-4">
                <div className="grid gap-2">
                    <Label htmlFor="name">Name</Label>
                    <Input
                        id="name"
                        type="name"
                        placeholder={AIRNEMOS_NAME}
                        required

                        onChange={(event) => dispatch({type: Actions.NAME, name: event.target.value})}
                        value={data.name}
                    />
                </div>
            </div>
        </CardContent>
    </>
}

export const Name: Step = {
    component: (data: Data, dispatch: Dispatch<AllActions>) => <Component data={data} dispatch={dispatch}></Component>,
    next: (index: number) => index + 1,
    previos: (index: number) => index - 1,
    canNext: (data: Data) => data.name != null && data.name.length > 0
}