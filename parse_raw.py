#!/bin/python

import fileinput
import sys
import os

def zeroLine():
	for i in range(0,512):
		output.write(chr(0x00))

output = open("sdcard01.img", "wb")

normal_lines = 0
zero_lines = 0
error_lines = 0

for line in fileinput.input():
	line = line.rstrip()
	if line == "Y":
		zero_lines += 1
		zeroLine()
	elif line == "Z":
		error_lines += 1
		zeroLine()
	else:
		if len(line) <> 1025:
			print >> sys.stderr, "short line (" + str(len(line)) + ")"
			error_lines += 1
			zeroLine()
		else:
			for i in range(0,1024,2):
				output.write( chr( int (line[i:i+2], 16 ) ) )
				normal_lines += 1


print >> sys.stderr, "normal: ", normal_lines
print >> sys.stderr, "zero: ", zero_lines
print >> sys.stderr, "error: ", error_lines
