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
            canNext.set(data.wifi.password != undefined && data.wifi.password.length >= 8)
        }
    
        export let data;
    </script>
    
    <Field type="password" label="setup_input_label_wifi_password" name="name" bind:value={data.wifi.password} on:change={validate} />