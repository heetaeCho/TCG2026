import subprocess
import os

path = os.path.dirname(os.path.abspath(__file__))
with open(f'{path}/URL.txt', 'r', encoding='utf-8') as f:
    for line in f.readlines():
        if line.startswith('-'):
            break
        https = line.split()[-1]
        command = ["git", "clone", https]
        subprocess.run(command)
