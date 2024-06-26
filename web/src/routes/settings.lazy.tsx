import { Button } from '@/components/ui/button'
import { Card, CardContent, CardDescription, CardHeader, CardTitle } from '@/components/ui/card'
import { Input } from '@/components/ui/input'
import { Label } from '@/components/ui/label'
import { createLazyFileRoute } from '@tanstack/react-router'

export const Route = createLazyFileRoute('/settings')({
  component: route
})

function route() {
    return (
        <Card>
            <CardHeader>
                <CardTitle>Update</CardTitle>
                <CardDescription>Aktuelle Version: {AIRNEMOS_VERSION}</CardDescription>
            </CardHeader>
            <CardContent>
                <div className="grid w-full max-w-sm items-center gap-1.5">
                    <Label htmlFor="firmware" aria-disabled>Firmware-Datei</Label>
                    <div className='flex gap-2'>
                        <Input id="firmware" type="file" />
                        <Button disabled>Update</Button>
                    </div>
                </div>
            </CardContent>
        </Card>
    )
}