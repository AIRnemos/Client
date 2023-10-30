import os

Import("env")

def build():
    print("Building Web-Client")
    os.system("cd web && npm run build")

build()