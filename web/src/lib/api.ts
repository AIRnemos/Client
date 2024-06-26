import wretch from "wretch"

export const APIClient = wretch("/api").resolve(r => r.json())