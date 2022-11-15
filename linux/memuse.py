#!/opt/homebrew/bin/python3

import subprocess

size = 100000000

print("Before:")
subprocess.run("free")

array = []*size


print("After:")
subprocess.run("free")
