#import re # import regular expressions module
import subprocess

print "Initializing..."
#config TODO - put this in a config file that the tester reads?
recolor_path = "../Debug/./recolor";
input_path = "../inputs/";
output_path = "../rc_test/outputs/";

class HandImage:
	name = ""
	average_color = [] #bgr
	filepath = ""
	maskpath = ""

	def __init__(self, name, average_color):
		#TODO check inputs
		self.name = name
		self.average_color = average_color
		self.filepath = self.name + ".jpg"
		self.maskpath = self.name + "_mask.jpg"

hands = {'hand_brown': HandImage("hand_brown", ["75.38", "108.19", "162.22"]), \
		 'hand_dark': HandImage("hand_dark", ["65.20", "91.83", "139.01"]), \
		 'hand_light': HandImage("hand_light", ["130.08", "153.18", "199.70"]), \
		 'hand_pale': HandImage("hand_pale", ["121.73", "134.91", "160.90"])}

def test_recol(orig_hand, target_hand):
	print "\nTesting " + orig_hand.name +  " to " + target_hand.name + "..."
	recol_out = subprocess.check_output([recolor_path, \
		input_path + orig_hand.filepath, \
		target_hand.average_color[0], target_hand.average_color[1], target_hand.average_color[2], \
		"-mfile", input_path + orig_hand.maskpath, \
		"-ofile", output_path + orig_hand.name + "-to-" + target_hand.name]);

	print "##### recolor output start #####"
	print recol_out
	print "##### recolor output end #####\n"

print "Testing recolor..."
test_recol(hands['hand_brown'], hands['hand_dark']);
test_recol(hands['hand_brown'], hands['hand_light']);
test_recol(hands['hand_brown'], hands['hand_pale']);

test_recol(hands['hand_dark'], hands['hand_light']);
test_recol(hands['hand_dark'], hands['hand_pale']);

test_recol(hands['hand_light'], hands['hand_pale']);

# project = "./" # specify the project folder
# in_file = "{}example.txt".format(project) # path to the txt-file relative to the project folder

# with open(in_file) as f:    # loads the file
#     content = f.read()
#     keys = re.findall(r"%(.+):", content)   # find the keys using RegEx
#     values = re.findall(r":\s*([\w\W]+?)\s*(?:%|$)", content) # find the values using RegEx

# options = zip(keys, values) # combining keys and values in one nested list

# print options