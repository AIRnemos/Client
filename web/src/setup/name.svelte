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
        return index + 1
    }

    export function previos(index) {
        return index - 1
    }

    onMount(() => {
        validate()
    })

    function validate() {
        canNext.set(data.name != undefined && data.name.length != 0)
    }

    export let data;
</script>

<Field type="text" label="setup_input_label_name" name="name" bind:value={data.name} on:change={validate} />
<Field type="checkbox" label="setup_input_label_buzzer" name="buzzer" bind:value={data.buzzer} />