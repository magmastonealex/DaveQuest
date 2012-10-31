import sys


infile = open(sys.argv[1], "r")
outfile = open(sys.argv[2], "w")

infile.readline()
infile.readline()
infile.readline()
infile.readline()
infile.readline()
infile.readline()
infile.readline()
for x in range(0,23):
	tempstr = infile.readline()
	newstr = tempstr[-2]
	newstr = tempstr[0:len(tempstr)-2]
	outfile.write(newstr+"\n");
tempstr = infile.readline()
outfile.write(tempstr)
