export const APIClient = {
    get: async <T = any>(path: string): Promise<T> => {
        const res = await fetch(`/api${path}`)

        if (res.status >= 300) {
            throw new Error("Wrong Status");
        } 

        return await res.json();
    },
     
    post: async (path: string, option?: RequestInit) => {
        const res = await fetch(`/api${path}`, {method: "POST", ...option})

        if (res.status >= 300) {
            throw new Error("Wrong Status", {cause: res});
        } 

        return await res.json();
    }
}