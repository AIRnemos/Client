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
import { wrap } from "svelte-spa-router/wrap"

export default {
    /*"/dashboard": wrap({
        asyncComponent: () => import("./pages/dashboard.svelte"),
        userData: {
            title: "page_dashboard_title"
        }
    }),*/
    "/settings": wrap({
        asyncComponent: () => import("./pages/settings.svelte"),
        userData: {
            title: "page_settings_title"
        }
    }),
    "*": wrap({
        asyncComponent: () => import("./pages/index.svelte"),
    })
}