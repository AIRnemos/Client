<script>
    import Fa from "svelte-fa";
    import { onMount } from "svelte";
    import { faCircleNotch, faExclamation } from "@fortawesome/free-solid-svg-icons";
    import { _ } from "svelte-i18n";
    import { APIClient } from "../lib/api";

    export function next(index) {
        return index + 1
    }

    export function previos(index) {
        return index - 1
    }

    let error = false
    let done = false

    function getConfig() {
        let config = {
            name: data.name,
            password: "",
            buzzer: data.buzzer == "checked",
            wifi: {
                mode: data.wifi.mode == "wifi" ? 2 : data.wifi.mode == "ap" ? 1 : 0,
                fallback: 1,
                ssid: data.wifi.ssid,
                password: data.wifi.password,
                retires: -1,
                ap: {
                    ssid: data.wifi.ap.ssid,
                    password: data.wifi.ap.password
                }
            },
        }
        return config
    }

    onMount(async () => {
        try {
            await APIClient.post("/setup", {
                body: JSON.stringify(getConfig())
            })

            done = true
        } catch (e) {
            error = true
        }
    })

    export let data;
    // Todo: messages
</script>


{#if error}
    <div class="center">
        <Fa icon={faExclamation} size="2x" />
        <span>{$_("todo")}</span>
    </div>
{:else if done}
    <div class="center">
        <Fa icon={faExclamation} size="2x" />
        <span>{$_("done")}</span>
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