<script>
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
    import Field from "../components/Field.svelte";
    import { canNext } from "./store";
    import { onMount } from "svelte";

    export function next(index) {
        return index + 4
    }

    export function previos(index) {
        if(data.wifi.ssid == `AIRnemos - ${data.name}`) data.wifi.ssid = ""
        return index - 1
    }

    onMount(() => {
        if(data.wifi.ssid == "") data.wifi.ssid = `AIRnemos - ${data.name}`
        validate()
    })

    function validate() {
        canNext.set((() => {
            if(data.wifi.ssid == undefined || data.wifi.ssid.length == 0) return false
            if(data.wifi.password == undefined || data.wifi.password.length <= 8) return false

            return true
        })())
    }

    export let data;
</script>

<Field label="setup_input_label_wifi_ap_name" name="ap-name" type="text" bind:value={data.wifi.ssid} on:change={validate} />
<Field label="setup_input_label_wifi_ap_password" name="ap-password" type="password" bind:value={data.wifi.password} on:change={validate}/>