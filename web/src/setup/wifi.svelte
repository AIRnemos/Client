<script>
    import Field from "../components/Field.svelte";
    import { canNext } from "./store";
    import { onMount } from "svelte";
    import { _ } from "svelte-i18n";

    export function next(index) {
        if(data.wifi.mode == "none") return index + 5
        if(data.wifi.mode == "wifi") return index + 2
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

<Field type="select" name="wifi" label="setup_input_label_wifi" bind:value={data.wifi.mode}>
    <option value="wifi">{ $_("setup_input_label_wifi_wifi") }</option>
    <option value="ap">{ $_("setup_input_label_wifi_ap") }</option>
    <option value="none">{ $_("setup_input_label_wifi_none") }</option>
</Field>