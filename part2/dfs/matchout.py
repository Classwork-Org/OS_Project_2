import re
import pprint

def main():

	print("Checking output vs ps command....");
	kmodOut= open("output.txt","r");
	psOut = open("ps.txt", "r").read();
	foundCount = 0;
	unmatchedPids = {};

	for eachLine in kmodOut:
		m = re.match('^.* pid: (?P<pid>[0-9]+).* name: (?P<name>.*),', eachLine);
		if m != None:
			if m.group('pid') in psOut:
				foundCount = foundCount + 1;
			else:
				unmatchedPids[m.group('pid')] = m.group('name')

	print("found " + str(foundCount) + " out of " + str(psOut.count('\n')-1) + " pids");
	print("couldn't find the following in ps out (" + str(len(unmatchedPids))  + "): ")
	pprint.pprint(unmatchedPids)

if __name__ == '__main__':
	main();
