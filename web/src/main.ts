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
