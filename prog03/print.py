import sys
import re

filename = sys.argv[1]

f = open(filename, "r")

data = []
size = 0

r = re.compile("(\d+)\s+(\d+)\s+(\d+)")

for line in f:
	if line.strip() == "":
		continue
	elif line[0] == "#":
		continue
	elif line[0] == "n":
		size = int(line[2:])
		data = []
		for i in range(0,size*size):
			data.append([0]*(size*size))
	else:
		m = r.match(line)
		data[int(m.group(1))-1][int(m.group(2))-1] = int(m.group(3))

for line in open("BonusManual.data"):
	if line.strip() == "":
		continue
	elif line[0] == "#":
		continue
	else:
		m = r.match(line)
		data[int(m.group(1))-1][int(m.group(2))-1] = int(m.group(3))

for ySub in range(0,size):
	for y in range(0,size):
		for xSub in range(0,size):
			for x in range(0,size):
				val = data[xSub*size+x][ySub*size+y]
				if val == 0:
					sys.stdout.write("   ")
				else:
					sys.stdout.write("%2d " % val)
			if xSub < size-1:
				sys.stdout.write(" | ")
		sys.stdout.write("\n")
	if ySub < size-1:
		for i in range(0,size*size*3 + (size-1)*3):
			sys.stdout.write("-")
		sys.stdout.write("\n")