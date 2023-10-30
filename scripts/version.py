import os

VERSION = os.getenv('VERSION', 'local-build')

if not os.path.exists("VERSION"):
    open("VERSION", "x")

with open("VERSION", "r+") as f:
    data = f.read()
    f.seek(0)
    f.write(VERSION)
    f.truncate()
    f.close()