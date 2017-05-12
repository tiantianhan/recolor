import re # import regular expressions module

import os

print "Testing recolor..."
#config TODO - put this in a config file that the tester reads?
recolor_path = "../Debug/./recolor";
input_path = "../inputs/";
output_path = "../rc_test/outputs/";


os.system(recolor_path + " " \
	+ input_path + "hand_brown.jpg" + " " \
	+ 130.08 + 153.18 + 199.70 + " " \
	+ "-mfile " + input_path + "hand_brown_mask.jpg" + " " \
	+ "-ofile " + output_path + "test");

project = "./" # specify the project folder
in_file = "{}example.txt".format(project) # path to the txt-file relative to the project folder

with open(in_file) as f:    # loads the file
    content = f.read()
    keys = re.findall(r"%(.+):", content)   # find the keys using RegEx
    values = re.findall(r":\s*([\w\W]+?)\s*(?:%|$)", content) # find the values using RegEx

options = zip(keys, values) # combining keys and values in one nested list

print options