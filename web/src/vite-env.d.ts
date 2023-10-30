/// <reference types="svelte" />
/// <reference types="vite/client" />

interface ImportMetaEnv {
    readonly AIRNEMOS_SETUP: string
    readonly AIRNEMOS_AP: string
}

declare const AIRNEMOS_VERSION: string;

declare let AIRNEMOS_NAME: string;
declare let AIRNEMOS_SETUP: bool;
declare let AIRNEMOS_AP: bool;