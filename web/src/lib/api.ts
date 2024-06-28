import wretch from "wretch"

export const APIClient = wretch("/api").resolve(r => r.json())
export const APIClientWO = wretch("/api").resolve(r => r.json())