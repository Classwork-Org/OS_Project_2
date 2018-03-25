import re
import pprint
from anytree import Node, RenderTree

def checkOutWithLinear():
	print("checking output with linear command output....")
	kmodOut= open("output.txt","r")
	linearModOut = open("../linear/output.txt").read()

	unmatchedLines = []
	foundCount = 0
	noOfProcesses = 0
	for eachLine in kmodOut:
		m = re.match('^.* pid: (?P<pid>[0-9]+).* name: (?P<name>.*),', eachLine)
		if m != None:
			noOfProcesses = noOfProcesses + 1
			if m.group('name') in linearModOut:
				foundCount = foundCount + 1
			else:
				unmatchedLines.append(eachLine)

	print("found " + str(foundCount) + " out of " + str(noOfProcesses) + " pids")
	
	if(len(unmatchedLines) != 0):
		print("couldn't find the following in linear out (" + str(len(unmatchedLines))  + "): ")
		pprint.pprint(unmatchedLines)

	return 0

def checkOutWithPs():
	print("Checking output vs ps command....")
	kmodOut= open("output.txt","r")
	psOut = open("ps.txt", "r")

	ps = {}
	#build ps tree
	#ps is dictionary of reference to all nodes
	#ps prevents having to search for node and for connecting children to parents (so heroic)
	root = Node(0)
	ps[0] = Node(0, parent = root)
	for eachLine in psOut:
		m = re.match('^[a-zA-Z \+\-\_]+(?P<pid>[0-9]+) +(?P<ppid>[0-9]+)', eachLine)
		if m != None:
			pid = int(m.group('pid'))
			ppid = int(m.group('ppid'))
			ps[pid] = Node(pid, parent = ps[ppid])

	#confirm relations
	matches = 0
	noOfProcesses = 0
	pidWithWrongParent = []
	pidsThatDontExist = []
	for eachLine in kmodOut:
		m = re.match('^.* pid: (?P<pid>[0-9]+), parent_pid: (?P<ppid>[0-9]+)', eachLine)
		if m != None:
			noOfProcesses = noOfProcesses + 1
			pid = int(m.group('pid'))
			ppid = int(m.group('ppid'))
			if pid in ps: 
				if ps[pid].parent.name == ppid:
					matches = matches + 1
				else:
					pidWithWrongParent.append(pid)
			else:
				pidsThatDontExist.append(pid)

	print(RenderTree(root))
	print "pids that pids that dont exist (always the insmod process that doest exist when calling ps command)"
	print pidsThatDontExist
	print "pids with Wrong Parent"
	print pidWithWrongParent
	print "number of pids with correctly matched parents"
	print matches
	print "total number of pids"
	print noOfProcesses 


def main():
	checkOutWithPs()
	checkOutWithLinear()



if __name__ == '__main__':
	main()
