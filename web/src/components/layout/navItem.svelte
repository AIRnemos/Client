<script lang="ts">
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