import { Button } from '@/components/ui/button'
import { Card, CardContent, CardDescription, CardHeader, CardTitle } from '@/components/ui/card'
import { Input } from '@/components/ui/input'
import { Label } from '@/components/ui/label'
import { APIClient } from '@/lib/api'
import { createLazyFileRoute } from '@tanstack/react-router'
import { AlertCircle, CheckCircle2, Loader2 } from 'lucide-react'
import { useState } from 'react'
import * as SparkMD5 from "spark-md5"

export const Route = createLazyFileRoute('/settings')({
  component: route
})

enum UpdateState {
    UPLOADING,
    RESTARTING,
    DONE,
    ERROR,

    NONE
}

function route() {
    const [updating, setUpdating] = useState(UpdateState.NONE);
    const [updateInfo, setUpdateInfo] = useState<any>()
    const [firmwareFile, setFirmwareFile] = useState<FileList | null>();

    async function updateViaUpload() {
        setUpdating(UpdateState.UPLOADING)

        if (firmwareFile == null || firmwareFile.length == 0) {
            setUpdating(UpdateState.NONE)
            return
        }

        let data = new FormData()
        let file = firmwareFile[0]
        let md5: string

        try {
            md5 = await (() => {
                return new Promise((res, rej) => {
                    // @ts-ignore
                    const blobSlice = File.prototype.slice || File.prototype.mozSlice || File.prototype.webkitSlice;
                    const chunkSize = 2097152; // Read in chunks of 2MB
                    const chunks = Math.ceil(file.size / chunkSize);
                    const spark = new SparkMD5.ArrayBuffer();
                    const fileReader = new FileReader();
                    let currentChunk = 0;
                    let loadNext: () => void;

                    fileReader.onload = (e: ProgressEvent<FileReader>) => {
                        spark.append(e.target?.result as ArrayBuffer);
                        currentChunk += 1;

                        if (currentChunk < chunks) {
                            loadNext();
                        } else {
                            res(spark.end())
                        }
                    };

                    fileReader.onerror = rej

                    loadNext = () => {
                        const start = currentChunk * chunkSize;
                        const end = ((start + chunkSize) >= file.size) ? file.size : start + chunkSize;

                        fileReader.readAsArrayBuffer(blobSlice.call(file, start, end));
                    };
                    loadNext();
                })
            })()
        } catch (err) {
            console.error(err)
            setUpdateInfo({
                updateRetry: true,
                updateError: "md5" 
            })
            setUpdating(UpdateState.ERROR)
            return
        }

        if(md5 == undefined) {
            setUpdateInfo({
                updateRetry: true,
                updateError: "md5-2" 
            })
            setUpdating(UpdateState.ERROR)
            return
        }

        data.append("MD5", md5)
        data.append("file", file)

        try {
            await APIClient.body(data).post("/update")
    
            setUpdating(UpdateState.RESTARTING);
    
            setTimeout(() => setUpdating(UpdateState.DONE), 3000);
        } catch(err: any) {
            if(err?.cause == undefined) {
                setUpdateInfo({
                    updateRetry: true,
                    updateError: "error" 
                })
                return
            }
            const res = await err.cause.json()
            
            setUpdateInfo({
                updateRetry: true,
                updateError: res.msg 
            })
            return
        }

        setUpdating(UpdateState.NONE)
    }

    let content
    if(updating != UpdateState.NONE) {
        let title: string
        let icon = <Loader2 size="4rem" className='animate-spin'/>
        let contentCard = <CardContent className='pb-0'></CardContent>

        switch (updating) {
            case UpdateState.UPLOADING:
                title = "Hochladen..."
                break
            case UpdateState.RESTARTING:
                title = "Neustarten..."
                break
            case UpdateState.DONE:
                title = "Fertig!"
                icon = <CheckCircle2 size="4rem" />
                contentCard = <CardContent>
                    <Button onClick={() => location.reload()}>Fenster neuladen</Button>
                </CardContent>
                break
            case UpdateState.ERROR:
                title = "Fehler"
                icon = <AlertCircle size="4rem" />
                contentCard = <CardContent>
                    <CardDescription>{JSON.stringify(updateInfo)}</CardDescription>
                    <Button onClick={updateViaUpload}>Nochmal</Button>
                </CardContent>
                break
        }

        content = <>
            <Card className='text-center'>
                <CardHeader>
                    <div className='flex justify-center'>
                        {icon}
                    </div>
                    <CardTitle>{title}</CardTitle>
                </CardHeader>
                {contentCard}
            </Card> 
        </>
    } else { 
        content = <>
            <Card>
                <CardHeader>
                    <CardTitle>Update</CardTitle>
                    <CardDescription>Aktuelle Version: {AIRNEMOS_VERSION}</CardDescription>
                </CardHeader>
                <CardContent>
                    <div className="grid w-full max-w-sm items-center gap-1.5">
                        <Label htmlFor="firmware" aria-disabled>Firmware-Datei</Label>
                        <div className='flex gap-2'>
                            <Input 
                                id="firmware" 
                                type="file" 
                                accept='.bin' 
                                onChange={(event) => setFirmwareFile(event.target.files)} />
                            <Button onClick={updateViaUpload}>Update</Button>
                        </div>
                    </div>
                </CardContent>
            </Card>
        </>
    }

    

    return content
}