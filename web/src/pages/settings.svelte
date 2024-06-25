<script lang="ts">
/*
    AIRnemos is a software for CO2 meter.
    Copyright (C) 2023 Quentin Schuster

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <https://www.gnu.org/licenses/>.
*/

    import { _ } from "svelte-i18n";
    import Card from "../components/layout/card.svelte"
    import { check as checkVersion, newest } from "../store/version";
    import Field from "../components/Field.svelte";
    import { APIClient } from "../lib/api";
    import Fa from "svelte-fa";
    import { faCheck, faCircleNotch, faExclamation } from "@fortawesome/free-solid-svg-icons";
    import * as SparkMD5 from "spark-md5"

    enum UpdateState {
        UPLOADING,
        DOWNLOADING,
        RESTARTING,
        DONE,
        ERROR,

        NONE
    }

    let loading = true

    let updating = false
    let state: UpdateState = UpdateState.NONE
    let updateRetry: boolean = false
    let updateError: string = ""
    let versionErr = false

    let reseting = false;
    let resetError = false;

    async function upload(value: CustomEvent<any>) {
        updating = true
        state = UpdateState.UPLOADING

        
        let data = new FormData()
        let file = value.detail
        let md5

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
                    let loadNext;

                    fileReader.onload = (e) => {
                        spark.append(e.target.result);
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
            updateRetry = true
            updateError = "0001-0000-00001" 
            state = UpdateState.ERROR
            return
        }

        if(md5 == undefined) {
            updateRetry = true
            updateError = "0001-0000-00002" 
            state = UpdateState.ERROR
            return
        }

        data.append("MD5", md5)
        data.append("file", value.detail)
        
        try {
            await APIClient.post("/update", {
                body: data
            })

            UpdateState.RESTARTING;

            setTimeout(() => state = UpdateState.DONE, 3000);
        } catch(err) {
            if(err.cause == undefined) {
                updateRetry = true
                updateError = "0001-0000-10001" 
                return
            }
            const res = await err.cause.json()
            
            switch (res.msg) {
                case 1:
                    updateRetry = true
                    updateError = "0000-0000-00001" 
                    break;
                case 2:
                    updateRetry = true
                    updateError = "0000-0000-00002" 
                    break;
                case 3:
                    updateRetry = true
                    updateError = "0000-0000-00003" 
                    break;
                case 4:
                    updateRetry = true
                    updateError = "0000-0000-00004" 
                    break;
                case 5:
                    updateRetry = true
                    updateError = "0000-0000-00005" 
                    break;
                case 6:
                    updateRetry = true
                    updateError = "0000-0000-00006" 
                    break;
                case 7:
                    updateRetry = true
                    updateError = "0000-0000-00007" 
                    break;
                case 8:
                    updateRetry = true
                    updateError = "0000-0000-00008" 
                    break;
                case 9:
                    updateRetry = true
                    updateError = "0000-0000-00009" 
                    break;
                case 10:
                    updateRetry = false
                    updateError = "0000-0000-00010" 
                    break;
                case 11:
                    updateRetry = false
                    updateError = "0000-0000-00011" 
                    break;
                case 12:
                    updateRetry = true
                    updateError = "0000-0000-00012" 
                    break;
                case 13:
                    updateRetry = true
                    updateError = "0000-0000-00013" 
                    break;
                case 14:
                    updateRetry = true
                    updateError = "0000-0000-00014" 
                    break;
            
                default:
                    updateRetry = true
                    updateError = "0000-0000-19999" 
                    break;
            }
            state = UpdateState.ERROR

            return
        }
    }

    async function update(value) {
        console.log(value)
    }

    async function init() {
        try {
            if(!AIRNEMOS_AP)
                checkVersion()
        } catch(err) {
            versionErr = true
        }
    }

    async function reset() {
        reseting = true;
        try {
            await APIClient.post("/reset")

            setTimeout(() => location.reload(), 3000);
        } catch(err) {
            reseting = false
            resetError = true;
            return
        }
    }

    init();
</script>
    
{ #if updating}
    <Card class="update">
        { #if state == UpdateState.UPLOADING}
            <Fa icon={faCircleNotch} spin="true" size="2x" />
            <span>{$_("page_settings_uploading")}</span>
        { :else if state == UpdateState.DOWNLOADING}
            <Fa icon={faCircleNotch} spin="true" size="2x" />
            <span>{$_("page_settings_updating")}</span>
        { :else if state == UpdateState.RESTARTING}
            <Fa icon={faCircleNotch} spin="true" size="2x" />
            <span>{$_("page_settings_restarting")}</span>
        { :else if state == UpdateState.DONE}
            <Fa icon={faCheck} size="2x" />
            <span>{$_("page_settings_updating_done")}</span>
        { :else if state == UpdateState.ERROR}
            <Fa icon={faExclamation} size="2x" />
            <span>{$_(updateRetry ? "error_retry" : "error_contact", {values: {error: updateError}})}</span>
        {/if}    
    </Card>
{ :else }
    <Card>
        <h1 class="title">{$_("page_settings_update_title")}</h1>
        <p>{$_("page_settings_current_version", { values: { version: AIRNEMOS_VERSION }})}</p>
    
        {#if true}
            <Field name="upload_update" type="file" accept=".bin" uploadText="page_settings_button_upload_and_update" on:upload={upload} label=""/>
        {:else if $newest == undefined}
            <p>{$_("page_settings_serach_for_version")}</p>
        {:else if versionErr == true}
            <p>{ $_("page_settings_serach_error") }</p>
        {:else if $newest == AIRNEMOS_VERSION}
            <p>{$_("page_settings_already_on_latest_version")}</p>
        {:else}
            <p>{$_("page_settings_newer_version")}</p>
            <button class="primary" on:click={update}>{$_("page_settings_button_update", { values: { version: $newest }})}</button>
        {/if}
    </Card>
    <Card>
        <h1>{$_("page_settings_reset_title")}</h1>
        <p>{$_("page_settings_reset_description")}</p>

        {#if resetError}
            <p>Error while reseting!</p>
        {/if}
       
        <button class="danger" on:click={reset} disabled={reseting}>
            {#if reseting}
                <Fa icon={faCircleNotch} spin="true" size="md" />
            {/if}
            {$_("page_settings_reset_button")}
        </button>
    </Card>
{/if}

<style lang="sass" global>
    :global(.update)
        padding: 4rem !important
        display: flex
        flex-direction: column
        align-items: center
        justify-content: center
        gap: 1rem
</style>