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
    import { canNext } from "./store";
    import { onMount } from "svelte";
    import { _ } from "svelte-i18n"

    export function next(index) {
        return index + 1
    }

    export function previos(index) {
        return index - 1
    }

    onMount(() => {
        canNext.set(true)
    })

    export let data;
</script>

<h1>{ $_("setup_welcome_title")}</h1>
<p>{ $_("setup_welcome_thanks")}</p>
<p>{ $_("setup_welcome_last_things")}</p>