import { defineConfig } from 'vite'
import { svelte } from '@sveltejs/vite-plugin-svelte'
import { promises as fs} from 'fs'


// https://vitejs.dev/config/
export default defineConfig(async ({mode}) => {
  let version = (await fs.readFile("../VERSION")).toString("utf8")

  return {
    plugins: [
      svelte(),
    ],
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
          target: "http://192.168.4.1",
          changeOrigin: false,
        }
      }
    }
  }
})
