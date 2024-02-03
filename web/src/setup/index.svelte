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
    import { _ } from "svelte-i18n"

    import { canNext, triggerBack, triggerNext } from "./store";
    import Card from "../components/layout/card.svelte";
    import Welcome from "./welcome.svelte";
    import Name from "./name.svelte";
    import Wifi from "./wifi.svelte";
    import WifiAp from "./wifi-ap.svelte";
    import WifiSearch from "./wifi-search.svelte";
    import WifiPassword from "./wifi-password.svelte";
    import Check from "./check.svelte";
    import Done from "./done.svelte";
    import WifiTest from "./wifi-test.svelte";

    interface ComponentOptions { 
      component: ConstructorOfATypedSvelteComponent
      hideNext?: Boolean
      hideBack?: Boolean
      hideSpacer?: Boolean
      textNext?: string
    }

    let index = 0
    let components: (ConstructorOfATypedSvelteComponent | ComponentOptions)[] = [
      Welcome, 
      Name, 
      Wifi, 
      WifiAp, 
      { component: WifiSearch, hideNext: true },
      { component: WifiPassword, textNext: "button_connect"}, 
      { component: WifiTest, hideNext: true, hideBack: true, hideSpacer: true }, 
      { component: Check, textNext: "button_done"}, 
      { component: Done, hideBack: true, hideNext: true}
    ];
    let currentComponent;

    $: showBack = !getComponentOption(index, "hideBack", false)
    $: showNext = !getComponentOption(index, "hideNext", false)
    $: showSpacer = !getComponentOption(index, "hideSpacer", false)
    $: nextText = getComponentOption(index, "textNext", "button_next")

    function next() {
      index = currentComponent.next(index)
    }

    function previos() {
      index = currentComponent.previos(index)
    }

    function getComponent(): ConstructorOfATypedSvelteComponent {
      return Object.keys(components[index]).includes("component") ? (components[index] as ComponentOptions).component : components[index] as ConstructorOfATypedSvelteComponent
    }

    function getComponentOption<K extends keyof ComponentOptions>(index: number, key: K, defaultValue: ComponentOptions[K]): ComponentOptions[K] {
      return Object.keys(components[index]).includes("component") ? (components[index] as ComponentOptions)[key] ?? defaultValue : defaultValue 
    }

    let data = {
      name: String(AIRNEMOS_NAME),
      buzzer: "checked",
      wifi: {
        mode: "0",
        ssid: "",
        password: "",
        retires: -1,

        fallback: {
          mode: 0,
          ssid: "",
          password: "",
          retires: -1,
        },

        secure: false,
      }
    }

    triggerBack.subscribe((value) => {
      if(!value) return

      previos()

      $triggerBack = false
    })

    triggerNext.subscribe((value) => {
      if(!value) return

      next()

      $triggerNext = false
    })
</script>

<div class="wrapper">
    <Card class="setup-card">
      <svelte:component this={ getComponent() } bind:this={currentComponent} bind:data={data}  />
      {#if showSpacer}
        <div class="spacer"></div>
      {/if}
      <div class="buttons">
        {#if showBack}
          {#if index != 0}
            <button class="" on:click={previos}>{ $_("button_back") }</button>
          {/if}
        {/if}
        {#if showNext}
          <button class="primary" on:click={next} disabled={ !$canNext }>{$_(nextText)}</button>
        {:else}
          <span></span>
        {/if}
      </div>
    </Card>
</div>

<style lang="sass">
  @import "../css/_breakpoints"

  .wrapper
      height: 100vh
      width: 100vw
      height: -webkit-fill-available
      overflow-y: scroll

      :global(.setup-card)
        min-height: -webkit-fill-available
        width: calc( 100vw - 4rem )

        overflow-y: scroll
        margin: 0
        border-radius: 0

        display: flex
        flex-direction: column

  :global(.setup-card) 
    .spacer
      flex-grow: 1

    .buttons
      display: flex
      gap: 0.5rem
      
      button,
      span
        flex-grow: 1

  @include sm
    .wrapper
      display: flex
      justify-content: center
      align-items: center

      :global(.setup-card)
        width: calc( 576px - 5rem )
        min-height: 20rem
        border-radius: 1rem
        margin: 0.5rem
        overflow-y: revert

  @include md
    .wrapper
      :global(.setup-card)
        width: calc( 768px - 5rem )

  @include lg
    .wrapper
      :global(.setup-card)
        width: calc( 992px - 5rem )
</style>