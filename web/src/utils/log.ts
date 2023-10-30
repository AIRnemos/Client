export function debug(message: String, ...optionalParams: any[]) {
    if(import.meta.env.DEV) {
        console.log(message, optionalParams)
    }
}