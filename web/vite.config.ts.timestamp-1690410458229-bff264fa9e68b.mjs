// vite.config.ts
import { defineConfig } from "file:///Users/quentinschuster/Documents/airnemos/client/web/node_modules/vite/dist/node/index.js";
import { svelte } from "file:///Users/quentinschuster/Documents/airnemos/client/web/node_modules/@sveltejs/vite-plugin-svelte/src/index.js";
import { promises as fs } from "fs";
var vite_config_default = defineConfig(async ({ mode }) => {
  let version = (await fs.readFile("../VERSION")).toString("utf8");
  return {
    plugins: [
      svelte()
    ],
    define: {
      "AIRNEMOS_VERSION": JSON.stringify(version + (mode != "production" ? "-development" : ""))
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
          changeOrigin: false
        }
      }
    }
  };
});
export {
  vite_config_default as default
};
//# sourceMappingURL=data:application/json;base64,ewogICJ2ZXJzaW9uIjogMywKICAic291cmNlcyI6IFsidml0ZS5jb25maWcudHMiXSwKICAic291cmNlc0NvbnRlbnQiOiBbImNvbnN0IF9fdml0ZV9pbmplY3RlZF9vcmlnaW5hbF9kaXJuYW1lID0gXCIvVXNlcnMvcXVlbnRpbnNjaHVzdGVyL0RvY3VtZW50cy9haXJuZW1vcy9jbGllbnQvd2ViXCI7Y29uc3QgX192aXRlX2luamVjdGVkX29yaWdpbmFsX2ZpbGVuYW1lID0gXCIvVXNlcnMvcXVlbnRpbnNjaHVzdGVyL0RvY3VtZW50cy9haXJuZW1vcy9jbGllbnQvd2ViL3ZpdGUuY29uZmlnLnRzXCI7Y29uc3QgX192aXRlX2luamVjdGVkX29yaWdpbmFsX2ltcG9ydF9tZXRhX3VybCA9IFwiZmlsZTovLy9Vc2Vycy9xdWVudGluc2NodXN0ZXIvRG9jdW1lbnRzL2Fpcm5lbW9zL2NsaWVudC93ZWIvdml0ZS5jb25maWcudHNcIjtpbXBvcnQgeyBkZWZpbmVDb25maWcsIGxvYWRFbnYgfSBmcm9tICd2aXRlJ1xuaW1wb3J0IHsgc3ZlbHRlIH0gZnJvbSAnQHN2ZWx0ZWpzL3ZpdGUtcGx1Z2luLXN2ZWx0ZSdcbmltcG9ydCB7IHByb21pc2VzIGFzIGZzfSBmcm9tICdmcydcblxuXG4vLyBodHRwczovL3ZpdGVqcy5kZXYvY29uZmlnL1xuZXhwb3J0IGRlZmF1bHQgZGVmaW5lQ29uZmlnKGFzeW5jICh7bW9kZX0pID0+IHtcbiAgbGV0IHZlcnNpb24gPSAoYXdhaXQgZnMucmVhZEZpbGUoXCIuLi9WRVJTSU9OXCIpKS50b1N0cmluZyhcInV0ZjhcIilcblxuICByZXR1cm4ge1xuICAgIHBsdWdpbnM6IFtcbiAgICAgIHN2ZWx0ZSgpLFxuICAgIF0sXG4gICAgZGVmaW5lOiB7XG4gICAgICAnQUlSTkVNT1NfVkVSU0lPTic6IEpTT04uc3RyaW5naWZ5KHZlcnNpb24gKyAobW9kZSAhPSBcInByb2R1Y3Rpb25cIiA/IFwiLWRldmVsb3BtZW50XCIgOiBcIlwiKSksXG4gICAgfSxcbiAgICBidWlsZDoge1xuICAgICAgcm9sbHVwT3B0aW9uczoge1xuICAgICAgICBvdXRwdXQ6IHtcbiAgICAgICAgICBlbnRyeUZpbGVOYW1lczogYGFzc2V0cy9bbmFtZV0uanNgLFxuICAgICAgICAgIGNodW5rRmlsZU5hbWVzOiBgYXNzZXRzL1tuYW1lXS5qc2AsXG4gICAgICAgICAgYXNzZXRGaWxlTmFtZXM6IGBhc3NldHMvW25hbWVdLltleHRdYFxuICAgICAgICB9XG4gICAgICB9XG4gICAgfSxcbiAgICBlbnZQcmVmaXg6IFwiQUlSTkVNT1NcIixcbiAgICBzZXJ2ZXI6IHtcbiAgICAgIHByb3h5OiB7XG4gICAgICAgIFwiL2FwaVwiOiB7XG4gICAgICAgICAgdGFyZ2V0OiBcImh0dHA6Ly8xOTIuMTY4LjQuMVwiLFxuICAgICAgICAgIGNoYW5nZU9yaWdpbjogZmFsc2UsXG4gICAgICAgIH1cbiAgICAgIH1cbiAgICB9XG4gIH1cbn0pXG4iXSwKICAibWFwcGluZ3MiOiAiO0FBQThVLFNBQVMsb0JBQTZCO0FBQ3BYLFNBQVMsY0FBYztBQUN2QixTQUFTLFlBQVksVUFBUztBQUk5QixJQUFPLHNCQUFRLGFBQWEsT0FBTyxFQUFDLEtBQUksTUFBTTtBQUM1QyxNQUFJLFdBQVcsTUFBTSxHQUFHLFNBQVMsWUFBWSxHQUFHLFNBQVMsTUFBTTtBQUUvRCxTQUFPO0FBQUEsSUFDTCxTQUFTO0FBQUEsTUFDUCxPQUFPO0FBQUEsSUFDVDtBQUFBLElBQ0EsUUFBUTtBQUFBLE1BQ04sb0JBQW9CLEtBQUssVUFBVSxXQUFXLFFBQVEsZUFBZSxpQkFBaUIsR0FBRztBQUFBLElBQzNGO0FBQUEsSUFDQSxPQUFPO0FBQUEsTUFDTCxlQUFlO0FBQUEsUUFDYixRQUFRO0FBQUEsVUFDTixnQkFBZ0I7QUFBQSxVQUNoQixnQkFBZ0I7QUFBQSxVQUNoQixnQkFBZ0I7QUFBQSxRQUNsQjtBQUFBLE1BQ0Y7QUFBQSxJQUNGO0FBQUEsSUFDQSxXQUFXO0FBQUEsSUFDWCxRQUFRO0FBQUEsTUFDTixPQUFPO0FBQUEsUUFDTCxRQUFRO0FBQUEsVUFDTixRQUFRO0FBQUEsVUFDUixjQUFjO0FBQUEsUUFDaEI7QUFBQSxNQUNGO0FBQUEsSUFDRjtBQUFBLEVBQ0Y7QUFDRixDQUFDOyIsCiAgIm5hbWVzIjogW10KfQo=
