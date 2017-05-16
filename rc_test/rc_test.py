import subprocess

print "Initializing..."
#config TODO - put this in a config file that the tester reads?
recolor_path = "../Debug/./recolor";
input_path = "../inputs/";
output_path = "../rc_test/outputs/debug/";
test_description = "****This is a debug test****\n"

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


def log(filepath, text):
	with open(filepath, 'w') as f:
		f.write(text)

def test_recol(orig_hand, target_hand):
	""" tests the recolor program with an original hand image and a target hand image, writing
		resulting image and log to the output file
	"""
	print "\nTesting " + orig_hand.name +  " to " + target_hand.name + "..."
	output_name = orig_hand.name + "_to_" + target_hand.name + ".jpg"

	recol_out = subprocess.check_output([recolor_path, \
		input_path + orig_hand.filepath, \
		target_hand.average_color[0], target_hand.average_color[1], target_hand.average_color[2], \
		"-mfile", input_path + orig_hand.maskpath, \
		"-ofile", output_path + output_name]);

	print "##### recolor output start #####"
	print recol_out
	print "##### recolor output end #####\n"

	log(output_path + output_name + "-log.txt", test_description + recol_out)

print "Testing recolor..."
test_recol(hands['hand_dark'], hands['hand_brown']);
test_recol(hands['hand_dark'], hands['hand_light']);
test_recol(hands['hand_dark'], hands['hand_pale']);

test_recol(hands['hand_brown'], hands['hand_dark']);
test_recol(hands['hand_brown'], hands['hand_light']);
test_recol(hands['hand_brown'], hands['hand_pale']);

test_recol(hands['hand_light'], hands['hand_dark']);
test_recol(hands['hand_light'], hands['hand_brown']);
test_recol(hands['hand_light'], hands['hand_pale']);

test_recol(hands['hand_pale'], hands['hand_dark']);
test_recol(hands['hand_pale'], hands['hand_brown']);
test_recol(hands['hand_pale'], hands['hand_light']);
