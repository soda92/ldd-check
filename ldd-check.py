#!/usr/bin/python
import argparse
import os
import shutil
import subprocess
import sys
from pathlib import Path

parser = argparse.ArgumentParser()
parser.add_argument("-cp", "--copy", help="copy found dll",
                    action="store_true")
parser.add_argument("path", help="program path")
args = parser.parse_args()

output = ""

try:
    output = subprocess.check_output(
        "ldd " + args.path, stderr=subprocess.STDOUT, shell=True)
    output = output.decode()
except subprocess.CalledProcessError as e:
    print(e.output)
    sys.exit(1)

OUT_PATH = Path(args.path).resolve().parent
MSYS_ROOT = Path(os.environ.get('HOME')).resolve().parent.parent
outputlines = output.splitlines()
for exe in outputlines:
    arr = exe.split()
    lib = arr[2]
    if not lib.startswith("/c"):
        p = Path.joinpath(MSYS_ROOT, lib[1:])
        print(p)
        if args.copy:
            shutil.copy(p, OUT_PATH)
