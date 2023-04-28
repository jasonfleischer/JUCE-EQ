#!/usr/bin/python

# Description:
# Checks that proper formatting is used in code
# Usage:
# Script output will show up in XCode as warnings and errors
# To run in terminal, from the project root directory run the following: 
# $ python3 Scripts/check_code_formatting.py

import re
import os
import sys
import log

def main():

	projectDir = os.getcwd()
	check_formatting_in_sources(projectDir + '/Source/')


def check_formatting_in_sources(directory):
	for filename in os.listdir(directory):
		f = os.path.join(directory, filename)
		fileNameChecks(f, filename)
		if os.path.isdir(f):
			log.XcodeError("Sources folder should not have folders, use virtual folders in xcode instead", f)
		if os.path.isfile(f) and not filename.endswith("DS_Store"):
			check_formatting_in_file(f, filename)

def check_formatting_in_package_sources(directory):
	for filename in os.listdir(directory):
		f = os.path.join(directory, filename)
		if os.path.isfile(f) and not filename.endswith("DS_Store"):
			fileNameChecks(f, filename)
			check_formatting_in_file(f, filename)
		if os.path.isdir(f):
			check_formatting_in_package_sources(f)

def fileNameChecks(file, filename):
	if ".DS_Store" == filename:
		return
	if re.search("[0-9]", filename) and not "extension" in filename.lower():
		log.Xcode("Filenames should not have numbers", file)
	if re.search("[-_&$#]", filename) or " " in filename:
		log.Xcode("Invalid characters found in filename", file)
	if filename.endswith(".swift"):
		if ("controller" in filename.lower() or "manager" in filename.lower()) and not "extension" in filename.lower():
			log.Xcode("Controllers or managers are not to be used. Use 'Service' instead or rename", file)
		if "interface" in filename.lower() and not "extension" in filename.lower():
			log.Xcode("Interfaces are not to be used. Use 'Protocol' instead or rename", file)

def check_formatting_in_file(file, filename):
	f = open(file, 'r')
	lines = f.readlines()
	count = 0
	prev_line = ""
	for line in lines:
		count += 1
		line_count = str(count)
		defaultChecks(file, line_count, line, prev_line)
		if filename.endswith(".swift"):
			swiftOnlyChecks(file, line_count, line, prev_line)
		prev_line = line
	f.close()

def defaultChecks(file, line_count, line, prev_line):
	if re.search("//[ ]*#import", line):
		log.Xcode("Remove commented out import", file, line_count)
	if "// Do any additional setup" in line:
		log.Xcode("Please remove line", file, line_count)
	if ";;" in line:
		log.Xcode("Double semi-colon", file, line_count)
	if prev_line.replace(" ", "") == "\n" and line.replace(" ", "") == "\n":
		log.Xcode("Double new line found", file, line_count )
	if re.search("==[ ]*NO", line) or re.search("NO[ ]*==", line) or re.search("==[ ]*YES", line) or re.search("YES[ ]*==", line) :
		log.Xcode("Please fix poor conditional logic", file, line_count)
	if re.search("[a-zA-Z] [ ]+[a-zA-Z{]", line) or re.search("[)][ ]+[)]", line):
		log.Xcode("Extra space between characters", file, line_count)
	if re.search("[a-zA-Z] [ ]+=", line) or re.search("= [ ]+[a-zA-Z]", line):
		log.Xcode("Extra space between equal sign", file, line_count)
	if re.search("//.*Log", line):
		log.Xcode("Possible commented out log. Please remove line", file, line_count)
	if "//" == line.strip():
		log.Xcode("Useless comment", file, line_count)
	if "//  Created by " in line or "//  Copyright ©" in line or "//  Copyright (c)" in line:
		log.Xcode("Remove these auto generated comments. This information bloats code and is already in README file", file, line_count)
	if line.strip().startswith("if"):
		loopCheck("if", file, line, line_count)
	if line.strip().startswith("for"):
		loopCheck("for", file, line, line_count)
	if line.strip().startswith("while"):
		loopCheck("while", file, line, line_count)	

def swiftOnlyChecks(file, line_count, line, prev_line):
	if ";" in line:
		log.Xcode("Remove semi-colon", file, line_count)
	if "{" == line.strip() or ")" == line.strip() or "(" == line.strip():
		log.Xcode("Collapse bracket", file, line_count)
	if line.strip().startswith("//") and not ("TODO:" in line or "FIXME:" in line):
		log.Xcode("Comment without 'TODO:' or 'FIXME:'", file, line_count)	
	if line.strip().startswith("/*") or line.strip().endswith("*/") or "///" in line:
		log.Xcode("Suspicious comment. Use code to explain what you are doing. (Rename the variable, Make a function, refactor) If all else fails Mark with 'TODO:' or 'FIXME:''", file, line_count)

def loopCheck(ifForOrWhileString, file, line, line_count):
	if re.search(ifForOrWhileString + " [ ]+[\(]", line):
		log.Xcode("Extra space between '" + ifForOrWhileString + "' and bracket", file, line_count)
	if re.search(ifForOrWhileString + "[\(]", line):
		log.Xcode("No space between '" + ifForOrWhileString + "' and bracket", file, line_count)

log.i("---STARTING---")
log.i("script: " + sys.argv[0] + "\n")
main()
log.i("\n---FINISHED---\n")
