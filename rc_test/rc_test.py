import subprocess

print "Initializing..."
#config TODO - put this in a config file that the tester reads?
recolor_path = "/Users/tina/projects/recolor/Debug/./recolor";
input_path = "/Users/tina/projects/recolor/inputs/";

#defaults
alpha = -1
debug = True

# output_path = "/Users/tina/projects/recolor/rc_test/outputs/debug/";
# test_description = "***This is a debug run****\n\n";
# algorithm = "pw_dark_corr"
# alpha = 1.1

#output_path = "../rc_test/outputs/20170516_boost_test/";
#test_description = "Full test of all hands in dataset 1 with simple brightening algorithm\n\n";
# algorithm = "linear"

# output_path = "../rc_test/outputs/20170516_proportional_test/";
# test_description = "Full test of all hands in dataset 1 with proportional brightening algorithm\n\n";
# algorithm = "pw"

# output_path = "../rc_test/outputs/20170516_proportional_corrected_test/";
# test_description = "Full test of all hands in dataset 1 with proportional brightening algorithm and correction for dark spots\n\n";
# algorithm = "pw_dark_corr"

# output_path = "../rc_test/outputs/20170517_proportional_corrected_test_alpha5/";
# test_description = "Full test of all hands in dataset 1 with proportional brightening algorithm and correction for dark spots\n\n";
# algorithm = "pw_dark_corr"
# alpha = 5

# output_path = "../rc_test/outputs/20170517_proportional_corrected_test_alpha10/";
# test_description = "Full test of all hands in dataset 1 with proportional brightening algorithm and correction for dark spots, alpha = 10\n\n";
# algorithm = "pw_dark_corr"
# alpha = 10

# output_path = "../rc_test/outputs/20170517_proportional_corrected_test_alpha3/";
# test_description = "Full test of all hands in dataset 1 with proportional brightening algorithm and correction for dark spots, alpha = 3\n\n";
# algorithm = "pw_dark_corr"
# alpha = 3

# output_path = "/Users/tina/projects/recolor/rc_test/outputs/20170521_proportional_corrected_test_alpha1p5/";
# test_description = "Full test of all hands in dataset 1 with proportional brightening algorithm and correction for dark spots, alpha = 1.5\n\n";
# algorithm = "pw_dark_corr"
# alpha = 1.5

# output_path = "/Users/tina/projects/recolor/rc_test/outputs/20170522_proportional_corrected_test_alpha1p3/";
# test_description = "Full test of all hands in dataset 1 with proportional brightening algorithm and correction for dark spots, alpha = 1.3\n\n";
# algorithm = "pw_dark_corr"
# alpha = 1.3

# output_path = "/Users/tina/projects/recolor/rc_test/outputs/20170522_proportional_corrected_test_alpha1p2/";
# test_description = "Full test of all hands in dataset 1 with proportional brightening algorithm and correction for dark spots, alpha = 1.2\n\n";
# algorithm = "pw_dark_corr"
# alpha = 1.2

output_path = "/Users/tina/projects/recolor/rc_test/outputs/20170522_proportional_corrected_test_alpha1p1/";
test_description = "Full test of all hands in dataset 1 with proportional brightening algorithm and correction for dark spots, alpha = 1.1\n\n";
algorithm = "pw_dark_corr"
alpha = 1.1

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

	input_args = [recolor_path, \
		input_path + orig_hand.filepath, \
		input_path + target_hand.filepath, \
		"-inmask", input_path + orig_hand.maskpath, \
		"-targmask", input_path + target_hand.maskpath, \
		"-ofile", output_path + output_name, \
		"-algo", algorithm];

	if algorithm == "pw_dark_corr":
		input_args.extend(["-alpha", str(alpha)])

	if debug:
		input_args.append("-d")

	recol_out = subprocess.check_output(input_args)

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
