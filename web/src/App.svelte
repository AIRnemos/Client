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