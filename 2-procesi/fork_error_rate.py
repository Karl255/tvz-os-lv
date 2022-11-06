#!/usr/bin/python3

import os
import subprocess
import sys

if len(sys.argv) < 2:
	print("Usage: ./%s count" % sys.argv[0])
	exit(1)

count = 1

try:
	count = int(sys.argv[1])
except ValueError:
	print("Argument is not a number")
	exit(2)

if count < 1:
	print("Argument can't be less than 1")
	exit(3)

for _ in range(20):
	call = subprocess.run(["./fork", str(count)], stdout = subprocess.PIPE, text = True)
	lastWasParent = False
	inverse_count = 0

	for line in call.stdout.split("\n"):
		if line.startswith("Roditelj"):
			if lastWasParent:
				inverse_count = inverse_count + 1

			lastWasParent = True
		else:
			lastWasParent = False

	print(inverse_count)
