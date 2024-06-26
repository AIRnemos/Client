import React from 'react'
import ReactDOM from 'react-dom/client'
import { RouterProvider, createRouter } from '@tanstack/react-router'
import "./app.css"

import { routeTree } from './routeTree.gen'
import { MeasurementProvider } from './provider/measurement'

const router = createRouter({ routeTree })

declare module '@tanstack/react-router' {
  interface Register {
    router: typeof router
  }
}

ReactDOM.createRoot(document.getElementById('root')!).render(
  <React.StrictMode>
    <MeasurementProvider>
      <RouterProvider router={router} />
    </MeasurementProvider>
  </React.StrictMode>,
)
