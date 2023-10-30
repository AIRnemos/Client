<script>
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