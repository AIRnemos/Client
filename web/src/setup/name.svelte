<script>
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