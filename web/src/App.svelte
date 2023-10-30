<script>
import Router, { replace } from "svelte-spa-router"
import { _ } from "svelte-i18n"
import { faHome, faGear } from '@fortawesome/free-solid-svg-icons'

import NavItem from "./components/layout/navItem.svelte";
import Setup from "./setup/index.svelte";

import routes from "./routes";

import Logo from "./assets/logo.svg"

let oldLocation = undefined;

let pageTitle = ""

function handleRouteLoading(e) {
    if (e?.detail?.location === oldLocation) {
        return;
    }
    oldLocation = e?.detail?.location;

    // resets
    pageTitle = e?.detail?.userData?.title;
}

function handleRouteFailure() {
    replace("/");
}
</script>

<svelte:head>
  {#if AIRNEMOS_SETUP}
  <title>{$_("setup_title")} - { $_("name") }</title>
  {:else}
    <title>{pageTitle ? $_(pageTitle) + " - " : ""} { AIRNEMOS_NAME } - { $_("name") }</title>
  {/if}
</svelte:head>

{#if AIRNEMOS_SETUP}
  <Setup />
{:else}
  <nav>
    <div class="top">
      <img src={Logo} alt="Logo">
      <span>{AIRNEMOS_NAME}</span>
    </div>
    <div class="links">
      <NavItem icon={faHome} link="#/dashboard" title="nav_dashboard_link"></NavItem>
      <NavItem icon={faGear} link="#/settings" title="nav_settings_link"></NavItem>
    </div>
    <div class="bottom">
      <span class="version">{ $_("name") } v{AIRNEMOS_VERSION}</span>
    </div>
  </nav>

  <main>
    <Router {routes} on:routeLoading={handleRouteLoading} on:conditionsFailed={handleRouteFailure}></Router>
  </main>
{/if}