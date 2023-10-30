<script>
    import { canNext } from "./store";
    import { onMount } from "svelte";
    import { _ } from "svelte-i18n"

    export function next(index) {
        return index + 1
    }

    export function previos(index) {
        if(data.wifi.mode == "none") return index - 5
        if(data.wifi.mode == "ap") return index - 4
        return index - 3
    }

    onMount(() => {
        canNext.set(true)
    })

    export let data;
</script>

<h1>{ $_("setup_check_title")}</h1>
<p>{ $_("setup_check_text")}</p>
{#if data.wifi.mode == "wifi"}
    <p>{ $_("setup_check_wifi", {values:{ip: data.wifi.ip}})}</p>
{:else if data.wifi.mode == "ap"}
    <p>{ $_("setup_check_ap")}</p>
{:else}
    <p>{ $_("setup_check_none")}</p>
{/if}
