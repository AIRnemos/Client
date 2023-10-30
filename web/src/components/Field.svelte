<script lang="ts">
    import { faAngleDoubleDown, faAngleDown, faAngleUp, faCheck, faEye, faEyeSlash } from "@fortawesome/free-solid-svg-icons";
    import { createEventDispatcher } from "svelte";
    import Fa from "svelte-fa";
    import { _ } from "svelte-i18n";

    export let type: string;
    export let value: any | undefined = undefined;

    const dispatch = createEventDispatcher();

    // common
    export let label: string
    export let err: string | undefined = undefined
    export let required: boolean = false
    export let name: string

    let inputRef

    const clickGlobal = (ev: Event) => {
        if(type == "color") {
            inputRef?.click()
        }
        else if(type == "checkbox") {
            ev.preventDefault()
            value = value == "checked" ? "unchecked" : "checked"
            return
        }
    }
    function click(ev: Event) {
        if(type == "password") {
            toggle = !toggle
            inputRef?.click();
        }

        clickGlobal(ev);
    }

    const up = () => {
        if(value == undefined) value = 0
        else value++

        inputRef?.focus()
    }

    const down = () => {
        if(value == undefined) value = 0
        else value--

        inputRef?.focus()
    }

    // password
    let toggle

    // file
    export let accept: string | undefined = undefined;
    export let uploadText: string | undefined = undefined;
    let fileInput
    let fileHighlighted = false

    function upload(event: MouseEvent) {
        event.preventDefault()
        dispatch("upload", value)
    }

    function chooseFile(event: MouseEvent) {
        event.preventDefault()
        fileInput.click(event)
    }

    function preventDefaults (event: DragEvent) {
        event.preventDefault()
        event.stopPropagation()
    }

    function highlightFile(event: DragEvent) {
        preventDefaults(event)
        fileHighlighted = true
    }
    function unhighlightFile(event: DragEvent) {
        preventDefaults(event)
        fileHighlighted = false
    }
    function handleFileDrop(event: DragEvent) {
        preventDefaults(event)
        unhighlightFile(event)

        let dataTransfer = event.dataTransfer
        let files = dataTransfer.files
        if(files == undefined) return
        if(files.length == 0) return

        let fileValue = dataTransfer.files[0]

        if(accept != undefined) {
            if(accept.toLowerCase().split(",").find((ending) => fileValue.name.toLowerCase().endsWith(ending)) == undefined) return
        }

        value = fileValue
    }

    function handleInput(ev) {
        value = type.match(/^(number|range)$/)
            ? +ev.target.value
            : ev.target.value;

        dispatch("change", value)
    }
</script>

{#if type == "file"}
<div class="drop_box" on:dragenter={highlightFile} on:dragover={highlightFile} on:dragleave={unhighlightFile} on:drop={handleFileDrop}>
    {#if fileHighlighted}
        <header>
            <h4>{$_("input_file_drop")}</h4>
        </header>
    {:else}
        <header>
            {#if value == undefined}
                <h4>{$_("input_file_select")}</h4>
            {:else}
                <h4>{value.name}</h4>
            {/if}
        </header>
        {#if accept != undefined}
            <p>{$_("input_file_accpeted", { values: { accept: accept }})}</p>
        {/if}
        <input bind:this={fileInput} type="file" hidden accept={accept} style="display:none;">
        <div>
            <button class="primary" on:click={chooseFile}>{$_("input_file_choose")}</button>
            {#if uploadText != undefined && value != undefined}
                <button class="primary" on:click={upload}>{$_(uploadText)}</button>
            {/if}
        </div>
    {/if}
</div>
{:else}
<div class="input-field" class:err={!!err}  class:input-checkbox={type == 'checkbox' }>
    {#if label && type != 'checkbox' }
        <label for={name}>{  $_(label) + (required ? "*" : "") }</label>
    {/if}
    <div class="input-wrapper" class:input-pointer={type == 'select'} class:input-color={type == 'color'} class:input-checkbox={ type == 'checkbox' } class:input-checked={ type == 'checkbox' && value == 'checked' } style:background={type == 'color' ? (value == undefined ? '#000000' : value) : undefined} on:click={clickGlobal}>
        {#if type == 'select'}
            <select
            name={name}
            id={name}
            bind:value={value}>
                <slot></slot>
            </select>
        {:else if type  == 'checkbox'}
            <button>
                <Fa icon={faCheck} style="color: #ffffff;" size="sm"/>
            </button>
        {:else}
            <input 
            bind:this={inputRef} 
            on:input={handleInput}
            value={value}
            
            name={name}
            id={name}
            type={type == 'password' && toggle ? 'text' : type}
            />
        {/if}
        <div class="icon" on:click={click}>
            {#if type == 'password' }
                <Fa icon={toggle ? faEyeSlash : faEye } />
            {/if}
            {#if type == 'select' }
                <Fa icon={ faAngleDown } />
            {/if}
            {#if type == 'number' }
                <div class="number">
                    <div on:click={up}>
                        <Fa icon={faAngleUp}/>
                    </div>
                    <div on:click={down}>
                        <Fa icon={faAngleDown} />
                    </div>
                </div>
            {/if}
        </div>
    </div>
    {#if type == 'checkbox' }
    <div>
        { #if label && type == 'checkbox'}
        <label for={ name } on:click={click}>{ $_(label) + (required ? "*" : "") }</label>
        {/if}
        {#if err}
        <span class="err-line">{{ err }}</span>
        {/if}
    </div>
    { :else }
    <span class="err-line">{ err ? err : "" }</span>
    {/if}
</div>
{/if}


<style lang="sass">
@use '../css/_color'
.drop_box
  margin: 10px 0
  padding: 30px
  display: flex
  align-items: center
  justify-content: center
  flex-direction: column
  border: 3px dotted #a3a3a3
  border-radius: 5px
  min-height: 15rem


.drop_box h4 
  font-size: 16px
  font-weight: 400
  color: #2e2e2e


.drop_box p 
  margin-top: 10px
  margin-bottom: 20px
  font-size: 12px
  color: #a3a3a3

.input-field
    display: flex
    flex-direction: column
    gap: 0.25rem

    .input-wrapper
        display: flex
        text-decoration: none
        color: #000000

        background: color.$white

        padding: 0

        border: 2px solid scale-color(color.$black, $lightness: 85%)
        border-radius: 0.5rem

        transition: border 0.25s

        height: 42px

        input, select
            border: none
            outline: none
            font-size: 1rem
            margin: 0.5rem
            background: #00000000
            width: 100%

        select
            appearance: none
            cursor: pointer

        input[type=color]
            cursor: pointer
            appearance: none

            &::-webkit-color-swatch
                border: none

        input::-webkit-outer-spin-button,
        input::-webkit-inner-spin-button
            -webkit-appearance: none
            margin: 0
        
        input[type=number]
            -moz-appearance: textfield

        input[type=checkbox]
            margin: 0
            height: 3rem

        &:hover
            border: 2px solid scale-color(color.$primary, $lightness: 60%)
        &:focus-within
            border: 2px solid scale-color(color.$primary, $lightness: 20%)

        .icon
            display: flex
            justify-content: center
            align-items: center
            padding-right: 0.75rem

            .number
                display: flex
                justify-content: center
                align-items: center
                flex-direction: column
                cursor: pointer

            &:hover
                cursor: pointer

        &.input-pointer,
        &.input-color
            cursor: pointer

        &.input-checked
            background: color.$primary

        &.input-checkbox
            height: 21px
            width: 21px !important
            padding: 0
            margin: 0

            button
                height: 21px
                width: 21px
                padding: 0
                margin: 0
                background: #00000000
                appearance: none
                border: none
                outline: none

        
    .err-line
        display: block
        min-height: 1.4em
        padding: 0

    &.err
        color: color.$danger

        .input-wrapper
            border-color: color.$danger

            &:focus-within
                border: 2px solid scale-color(color.$danger, $lightness: -45%)

    &.input-checkbox
        display: flex
        flex-direction: row
        align-items: center
        padding-bottom: 1.4em

        .input-wrapper
            width: 42px

            display: flex
            align-items: center
            justify-content: center
            flex-wrap: wrap
            flex-direction: column
</style>