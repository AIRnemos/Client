
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