import { defineConfig } from 'vite'
import react from '@vitejs/plugin-react'
import { TanStackRouterVite } from '@tanstack/router-plugin/vite'
import path from 'path'
import { promises as fs} from 'fs'

// https://vitejs.dev/config/
export default defineConfig(async ({mode}) => {
  let version = (await fs.readFile("../VERSION")).toString("utf8")

  return {
    plugins: [
      TanStackRouterVite(),
      react()
    ],
    resolve: {
      alias: {
        "@": path.resolve(__dirname, "./src"),
      },
    },
    define: {
      'AIRNEMOS_VERSION': JSON.stringify(version + (mode != "production" ? "-development" : "")),
    },
    build: {
      rollupOptions: {
        output: {
          entryFileNames: `assets/[name].js`,
          chunkFileNames: `assets/[name].js`,
          assetFileNames: `assets/[name].[ext]`
        }
      }
    },
    envPrefix: "AIRNEMOS",
    server: {
      proxy: {
        "/api": {
          target: "http://192.168.1.52",
          changeOrigin: false,
        }
      }
    }
  }
})
