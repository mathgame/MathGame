#!/usr/bin/python
import sys
import os.path
import random
import time

from datetime import datetime


random.seed(datetime.now())
epoch_time = int(time.time())

if (len(sys.argv) > 3) or (len(sys.argv) < 2) :
	print "--- debug(1)"
	print "Please specify component name, WITHOUT 'Component' in the end!"
	print "Or use 'create_component -remove compName'"
	print "Or use 'create_component -init_mgr'"
	print "Example:"
	print "create_component GameResources"
	print "will create GameResourcesComponent class in GameResourcesComponent.cpp and GameResourcesComponent.h files"
	print "and will register GameResources component in component factory."
	sys.exit()

commandStr = sys.argv[1]
compName = ""
compNameUpperCase = ""

if (commandStr[0] == '-'):
	if (len(sys.argv) == 3):
		compName = sys.argv[2]
else:
	# no command
	compName = commandStr
	commandStr = ""

compNameUpperCase = compName.upper()

compDirectoryName = "./"
factoryDirectoryName = "Settings/"
factorySysDirectoryName = "System/"
compCPPFile = compName + "Component.cpp"
compHFile = compName + "Component.h"
includeString = "#include \"../" + compHFile + "\""
registerString = "    CUSTOM_COMPONENT_MACRO(" + compName + ", foo)\\"
registerMarkerString = "// DO NOT DELETE THIS AND DO NOT PUT EMPTY LINE, THIS IS CREATE COMPONENT SCRIPT REGISTER MARKER"
includeMarkerString = "// DO NOT DELETE THIS AND DO NOT PUT EMPTY LINE, THIS IS CREATE COMPONENT SCRIPT INCLUDE MARKER"
randomStr = str(epoch_time)

if (commandStr == ""):
#{
	# No command, so we'll create a new component
	print compCPPFile
	print compHFile

	if os.path.isfile(compDirectoryName + compCPPFile) == True or os.path.isfile(compDirectoryName + compHFile):
		print "Component already exist!"
		sys.exit()

	print compName

	f = open(factoryDirectoryName + "ComponentsList.h", 'r')
	factoryData = f.read()
	f.close()

	if includeString in factoryData:
		print "Component already registered in ComponentsList.h"
		sys.exit()

	if registerString in factoryData:
		print "Component already registered in ComponentsList.h"
		sys.exit()

	factoryData = factoryData.replace(includeMarkerString, includeString + "\n" + includeMarkerString);
	factoryData = factoryData.replace(registerMarkerString, registerString + "\n" + registerMarkerString);

	f = open(factoryDirectoryName + "ComponentsList.h", 'w')
	f.write(factoryData)
	f.close()

	f = open(factorySysDirectoryName + "empty_comp_h",'r')
	filedata = f.read()
	f.close()

	newdata = filedata.replace("$$CompName$$",compName)
	newdata = newdata.replace("$$COMPNAME$$",compNameUpperCase)
	newdata = newdata.replace("$$RANDOM$$", randomStr) 

	f = open(compDirectoryName + compHFile,'w')
	f.write(newdata)
	f.close()

	f = open(factorySysDirectoryName + "empty_comp_cpp",'r')
	filedata = f.read()
	f.close()

	newdata = filedata.replace("$$CompName$$",compName)
	newdata = newdata.replace("$$COMPNAME$$",compNameUpperCase)
	newdata = newdata.replace("$$RANDOM$$", randomStr)

	f = open(compDirectoryName + compCPPFile,'w')
	f.write(newdata)
	f.close()
	print "Component ready!"
	sys.exit()
#}
elif (commandStr == "-remove"):
#{
	# Remove component
	with open(factoryDirectoryName + "ComponentsList.h") as f:
		content = f.readlines()
	newContent = list()
	for ln in content:
		if includeString in ln:
			continue
		if registerString in ln:
			continue
		newContent.append(ln)
	
	f = open(factoryDirectoryName + "ComponentsList.h",'w')
	for item in newContent:
		f.write("%s" % item)
	f.close()

	os.remove(compDirectoryName + compHFile);
	os.remove(compDirectoryName + compCPPFile);
	print "Component removed!"
	sys.exit()
#}
elif (commandStr == "-init_mgr"):
#{
	# Init manager
	f = open(factorySysDirectoryName + "ComponentsFactory.h",'r')
	filedata = f.read()
	f.close()

	newdata = filedata.replace("EMPTYLOCK", randomStr) 

	f = open(factorySysDirectoryName + "ComponentsFactory.h",'w')
	f.write(newdata)
	f.close()
	print "Init ready!"
	sys.exit()
#}

print "--- debug(2)"
print "Please specify component name, WITHOUT 'Component' in the end!"
print "Or use 'create_component -remove compName'"
print "Or use 'create_component -init_mgr'"
print "Example:"
print "create_component GameResources"
print "will create GameResourcesComponent class in GameResourcesComponent.cpp and GameResourcesComponent.h files"
print "and will register GameResources component in component factory."
sys.exit()
