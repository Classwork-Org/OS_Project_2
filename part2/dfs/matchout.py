import re
import pprint
from anytree import Node, RenderTree
from anytree.exporter import JsonExporter
import json

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
				unmatchedLines.append(m.group('name'))

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
	ps[0] = Node(0, parent = root, psname = "root", m = 'True')
	for eachLine in psOut:
		m = re.match('^[a-zA-Z \+\-\_]+(?P<pid>[0-9]+) +(?P<ppid>[0-9]+) .* (?P<name>.+)', eachLine)
		if m != None:
			pid = int(m.group('pid'))
			ppid = int(m.group('ppid'))
			ps_name = str(m.group('name'))
			#check if parent already exists, if it doesnt create it
			if ppid not in ps:
				ps[ppid] = Node(ppid)

			#check if child already exists
			#if it does connect it to parent
			#if it doesnt, create it and connect it to parent
			#parent node guaranteed to exist here
			if pid in ps:
				ps[pid].parent = ps[ppid]
				ps[pid].psname = ps_name
			else:
				ps[pid] = Node(pid, parent = ps[ppid], psname = ps_name, m = "False")

	#confirm relations
	matches = 0
	noOfProcesses = 0
	pidWithWrongParent = []
	pidsThatDontExist = []
	for eachLine in kmodOut:
		m = re.match('^.* pid: (?P<pid>[0-9]+), parent_pid: (?P<ppid>[0-9]+), name: (?P<name>.+),', eachLine)
		if m != None:
			noOfProcesses = noOfProcesses + 1
			pid = int(m.group('pid'))
			ppid = int(m.group('ppid'))
			name = str(m.group('name'))
			if pid in ps: 
				if ps[pid].parent.name == ppid:
					matches = matches + 1
					ps[pid].m = "True"
				else:
					pidWithWrongParent.append((pid,ppid))
			else:
				pidsThatDontExist.append((pid,name))

	#append name to match info and ids 
	for i in ps:
		ps[i].name = "name: \"" + ps[i].psname + "\", pid:" + str(ps[i].name) + ", m: " +\
		ps[i].m

	exporter = JsonExporter(indent = 2, sort_keys=True)
	output = exporter.export(root)
	with open('psout.json','w') as outfile:
		outfile.write(exporter.export(root))

	print "pids that dont exist"
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
