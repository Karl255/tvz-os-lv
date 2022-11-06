#!/usr/bin/python3

from distutils import text_file
import os
import subprocess
import sys

def saveToFile(name, items):
	with open(name, "w") as f:
		f.writelines(map(lambda value: "%s\n" % value, items))

if len(sys.argv) != 3:
	print("Usage: ./measure_all.py test_file buffer_size")
	exit(-1)

programs = ["./cp_sys", "./cp_std", "cp"]
buffer_size = 1024
test_file = ""
copy_file = "TEMP_COPY"

try:
	test_file = sys.argv[1]
	buffer_size = int(sys.argv[2])
except ValueError:
	print("Invalid value for 2nd argument: %s" % sys.argv[2])
	exit(-2)

if not os.path.exists(test_file):
	print("File %s does not exist" % test_file)
	exit(-3)

for program in programs:
	command = ["bash", "-c", "time %s %s %s %s" % (program, "-b=%s" % buffer_size if program != "cp" else "", test_file, copy_file)]
	times = []
	
	print("Measuring %s:" % program)
	
	for _ in range(20):
		call = subprocess.run(command, stdout = subprocess.DEVNULL, stderr=subprocess.PIPE, text = True)
		os.remove(copy_file)
		
		timeStrs = call.stderr[call.stderr.find("real") + 5:call.stderr.find("user") - 2].split("m")
		time = int(timeStrs[0]) * 60 + float(timeStrs[1])
		times.append(time)
		print(time)
	
	saveToFile("result-%s-buffer_%s-%s.txt" % (program if program == "cp" else program[2:], buffer_size, test_file), times)
