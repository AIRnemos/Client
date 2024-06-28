import React from 'react'
import ReactDOM from 'react-dom/client'
import { RouterProvider, createRouter } from '@tanstack/react-router'
import "./app.css"

import { routeTree } from './routeTree.gen'
import { MeasurementProvider } from './provider/measurement'

function stringToBool(value: string): boolean {
  return value == "false" ? false : true;
}

AIRNEMOS_SETUP = import.meta.env.DEV ? stringToBool(import.meta.env.AIRNEMOS_SETUP) : stringToBool(AIRNEMOS_SETUP)
AIRNEMOS_AP = import.meta.env.DEV ? stringToBool(import.meta.env.AIRNEMOS_AP) : stringToBool(AIRNEMOS_AP)

const router = createRouter({ routeTree })

declare module '@tanstack/react-router' {
  interface Register {
    router: typeof router
  }
}

async function loadSetup() {
  const Setup = (await import("./setup")).Setup
  return <Setup />
}

async function start() {
  const inner = AIRNEMOS_SETUP ? 
    await loadSetup() :
    <MeasurementProvider>
        <RouterProvider router={router} />
      </MeasurementProvider>

  ReactDOM.createRoot(document.getElementById('root')!).render(
    <React.StrictMode>
      {AIRNEMOS_SETUP}
      { inner }
    </React.StrictMode>,
  ) 
}

start()