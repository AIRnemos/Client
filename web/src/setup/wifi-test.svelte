<script lang="ts">
    import { faCircleNotch, faExclamation } from "@fortawesome/free-solid-svg-icons";
    import { APIClient } from "../lib/api";
    import { _ } from "svelte-i18n";
    import { blockSearch, canNext, triggerBack, triggerNext } from "./store";
    import { onMount } from "svelte";
    import Fa from "svelte-fa";

    let error = false

    export function next(index) {
        return index + 1
    }

    export function previos(index) {
        return index - 1
    }

    onMount(async () => {
        canNext.set(false)
        $blockSearch = true

        try {
            const result = await APIClient.post("/wifi/check", {
                body: JSON.stringify({
                    ssid: data.wifi.ssid,
                    password: data.wifi.secure ? data.wifi.password : undefined
                })
            })


            if(!result.success) throw "not connected"

            data.wifi.ip = result.ip
            
            $triggerNext = true
        } catch (err) {
            error = true
        }
        $blockSearch = false
    })

    export let data;
</script>

{#if error}
    <div class="center">
        <Fa icon={faExclamation} size="2x" />
        <span>{$_("error_setup_wifi_connect")}</span>
        <button on:click={() => $triggerBack = true}>{ $_("button_back") }</button>
    </div>
   
{:else}
    <div class="center">
        <Fa icon={faCircleNotch} spin="true" size="2x" />
        <span>{$_("loading")}</span>
    </div>
{/if}

<style lang="sass">
    .center
        display: flex
        flex-direction: column
        justify-content: center
        align-items: center
        gap: 1rem
        flex-grow: 1
</style>