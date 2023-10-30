<script lang="ts">
    import { canNext, loadingWiFis, loadingWiFisError, triggerNext, wifis } from "./store";
    import { onMount } from "svelte";
    import Fa from 'svelte-fa'
    import { _ } from "svelte-i18n";
    import { faCircleNotch, faExclamation, faLock } from "@fortawesome/free-solid-svg-icons";

    export function next(index) {
        return index + (data.wifi.secure ? 1 : 2)
    }

    export function previos(index) {
        return index - 2
    }

    onMount(async () => {
        canNext.set(true)
    })

    function selectWifi(wifi: any) {
        return () => {
            if(data.wifi.ssid != wifi.ssid)
                data.wifi.password = ""
                
            data.wifi.ssid = wifi.ssid
            data.wifi.secure = wifi.secure

            $triggerNext = true
        }
    }

    export let data;
</script>
{#each $wifis as wifi}
    <button on:click={selectWifi(wifi)}>
        <span>{wifi.ssid}</span>
        <span class="spacer"></span>
        {#if wifi.secure}
            <Fa icon={faLock}></Fa>
        {/if}
    </button>
{/each}

{#if $loadingWiFis}
    <div class="center">
        <Fa icon={faCircleNotch} spin="true" size="1x" />
        <span>{$_("loading")}</span>
    </div>
{/if}
{#if $loadingWiFisError != undefined }
    <div class="center">
        <Fa icon={faExclamation} size="1x" />
        <span>{$_("error_setup_wifi_search_loading", {values: {error: $loadingWiFisError}})}</span>
    </div>
{/if}

<style lang="sass">
    button
        display: flex
        .spacer
            flex-grow: 1

    .center
        padding-top: 1rem 
        display: flex
        justify-content: center
        align-items: center
        gap: 0.5rem
</style>