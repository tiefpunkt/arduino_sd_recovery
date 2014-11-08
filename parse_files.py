#!/bin/python
import re
import fileinput

# Header for each file, with filename and size
prog = re.compile('^--- (.*);(\d*)')


raw = fileinput.input()

while (True):
	first = raw.readline()
	if len(first) == 0:
		break
	second = raw.readline()
	header = prog.match(first)
	name = header.group(1)
	size = int(header.group(2))

	print "Name: " + name
	print "Size: " + str(size)
	print "Length: " + str(len(second))
	if len(second) - 1 <> size * 2:
		print "Size mismatch. Skipping."
	else:
		print "Size matches, writing file..."
		
		output = open("out/" + name, "wb")

		for i in range(0,size*2,2):
			output.write( chr( int (second[i:i+2], 16 ) ) )

		output.close()
	print "---"
