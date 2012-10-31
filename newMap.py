import sys

infile = open(sys.argv[1], "r")
outfile = open(sys.argv[1]+".door.txt.test", "w")
for y in range(0,23):
	instr = infile.readline()
	intup = instr.split(",")
	x=0
	for currNum in intup:
		if int(currNum) == 6:
			print("Door Found: ",x," ",y)
			outfile.write(input("Target > ") + "\n")
		x+=1;
