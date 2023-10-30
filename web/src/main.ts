import './css/app.sass'
import App from './App.svelte'
import initLang from './i18n'
import { waitLocale } from 'svelte-i18n'

function stringToBool(value: string): boolean {
  return value == "false" ? false : true;
}

AIRNEMOS_SETUP = import.meta.env.DEV ? stringToBool(import.meta.env.AIRNEMOS_SETUP) : stringToBool(AIRNEMOS_SETUP)
AIRNEMOS_AP = import.meta.env.DEV ? stringToBool(import.meta.env.AIRNEMOS_AP) : stringToBool(AIRNEMOS_AP)

let app
async function start() {
  initLang()

  await waitLocale()

  app = new App({
    target: document.getElementById('app'),
  })
}
start();

export default app
