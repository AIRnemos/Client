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

import active from 'svelte-spa-router/active'
import { _ } from "svelte-i18n"
import Fa from 'svelte-fa'
import type { IconDefinition } from "@fortawesome/free-solid-svg-icons";

export let icon: IconDefinition
export let link: string
export let title: string
</script>

<a href={link} class="button active" use:active>
    <Fa {icon} size="lg"></Fa>
    <span>{ $_(title) }</span>
</a>

<style lang="sass">
@import "../../css/_breakpoints"

a
    span
        display: none

@include lg
    .button
        width: 14rem
        display: flex
        span
            margin: 0 auto

        &.active
            background: #D4E5FF
        span
            display: unset
</style>