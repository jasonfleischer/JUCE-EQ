#!/usr/bin/python

# Description:
# log for scripts

def XcodeError(msg, file, line_count=0):
	print(file + ":" + str(line_count) + ": error: From custom script. " + msg)

def Xcode(msg, file, line_count=0):
	print(file + ":" + str(line_count) + ": warning: From custom script. " + msg)

def i(msg):
	print(msg)

def e(msg):
	RED = '\033[91m'
	ENDC = '\033[0m'
	print(f"{RED}{msg}{ENDC}")
