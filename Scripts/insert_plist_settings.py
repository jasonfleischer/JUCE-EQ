#!/usr/bin/python

# Description:
# Adds key value strings to plists
# To run in terminal, from the project root directory run the following: 
# $ python3 Scripts/insert_plist_settings.py

import re
import os
import sys
import log
import fileinput

def main():

	projectDir = os.getcwd()

	plistDir = projectDir + '/Builds/MacOSX/'
	plistAU = plistDir + 'Info-AU.plist'
	plistVST3 = plistDir + 'Info-VST3.plist'
	plistStandalone = plistDir + 'Info-Standalone_Plugin.plist'
	plistFiles = [plistAU, plistVST3, plistStandalone]

	for plistFile in plistFiles:
		insertIconFile("Icon.icns", plistFile)
		insertKeyValue("NSMicrophoneUsageDescription", "This app requires audio input. If you do not have an audio interface connected it will use the built-in microphone.", plistFile)
		insertKeyValue("NSBluetoothAlwaysUsageDescription", "This app requires bluetooth usage.", plistFile)
		insertKeyValue("NSHumanReadableCopyright", "Taurus Studios", plistFile)
	

def insertKeyValue(keyString, valueString, plistFile):
	fileContents = ""
	with open(plistFile, 'r') as reader:
		fileContents = reader.read()
	if not keyString in fileContents:
		skipNextLine = False
		for line in fileinput.input(plistFile, inplace=1):
			if "<plist>" in line:
				line = line.replace("<plist>","<plist>\n  <dict>\n\t<key>"+keyString+"</key>\n\t<string>"+valueString+"</string>")
				sys.stdout.write(line)
				skipNextLine = True
			elif skipNextLine:
				skipNextLine = False
			else:
				sys.stdout.write(line)


def insertIconFile(iconFile, plistFile):
	skipNextLine = False
	for line in fileinput.input(plistFile, inplace=1):	
		if "<key>CFBundleIconFile</key>" in line:
			line = line.replace("<key>CFBundleIconFile</key>","<key>CFBundleIconFile</key>\n\t<string>"+iconFile+"</string>")
			sys.stdout.write(line)
			skipNextLine = True
		elif skipNextLine:
			skipNextLine = False
		else:
			sys.stdout.write(line)

log.i("---STARTING---")
log.i("script: " + sys.argv[0] + "\n")
main()
log.i("\n---FINISHED---\n")

