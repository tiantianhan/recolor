import re # import regular expressions module

import os

print "TESTING"
os.system("../recolor/Debug/./recolor")

project = "./" # specify the project folder
in_file = "{}example.txt".format(project) # path to the txt-file relative to the project folder

with open(in_file) as f:    # loads the file
    content = f.read()
    keys = re.findall(r"%(.+):", content)   # find the keys using RegEx
    values = re.findall(r":\s*([\w\W]+?)\s*(?:%|$)", content) # find the values using RegEx

options = zip(keys, values) # combining keys and values in one nested list

print options