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