import os

print "Initializing..."
frame_code_ref_file = "frame_code_ref.txt" # txt file containing the latex code for table
frame_code_label_file = "frame_code_label.txt"
row_code_file = "row_code.txt" # txt file containing the latex code for each row

# basic_info = {"PY_NAME": "debug_test", \
#  	"PY_DESC": "Test results of a debug run."};
# results_path = "../rc_test/outputs/20170516_proportional_corrected_test/"

# basic_info = {"PY_NAME": "boost_test", \
#  	"PY_DESC": "Test results of simple addition / subtraction brightening function."};
# results_path = "../rc_test/outputs/20170516_boost_test/"

# basic_info = {"PY_NAME": "prop_test", \
#  	"PY_DESC": "Test results of brightening proportionally based on distance of color to the average."};
# results_path = "../rc_test/outputs/20170516_proportional_test/"

# basic_info = {"PY_NAME": "prop_correct_test", \
# 	"PY_DESC": "Test results of proportional brightening with correction for dark spots"};
# results_path = "../rc_test/outputs/20170516_proportional_corrected_test/"

# basic_info = {"PY_NAME": "prop_correct_test_a5", \
# 	"PY_DESC": "Test results of proportional brightening with correction for dark spots"};
# results_path = "../rc_test/outputs/20170517_proportional_corrected_test_alpha5/"

# basic_info = {"PY_NAME": "prop_correct_test_a10", \
# 	"PY_DESC": "Test results of proportional brightening with correction for dark spots, alpha = 10"};
# results_path = "../rc_test/outputs/20170517_proportional_corrected_test_alpha10/"

# basic_info = {"PY_NAME": "prop_correct_test_a3", \
# 	"PY_DESC": "Test results of proportional brightening with correction for dark spots, alpha = 3"};
# results_path = "../rc_test/outputs/20170517_proportional_corrected_test_alpha3/"

# basic_info = {"PY_NAME": "prop_correct_test_a1p5", \
# 	"PY_DESC": "Test results of proportional brightening with correction for dark spots, alpha = 1.5"};
# results_path = "../rc_test/outputs/20170521_proportional_corrected_test_alpha1p5/"

# basic_info = {"PY_NAME": "prop_correct_test_a1p3", \
# 	"PY_DESC": "Test results of proportional brightening with correction for dark spots, alpha = 1.3"};
# results_path = "../rc_test/outputs/20170522_proportional_corrected_test_alpha1p3/"

# basic_info = {"PY_NAME": "prop_correct_test_a1p2", \
# 	"PY_DESC": "Test results of proportional brightening with correction for dark spots, alpha = 1.2"};
# results_path = "../rc_test/outputs/20170522_proportional_corrected_test_alpha1p2/"

# basic_info = {"PY_NAME": "prop_correct_test_a1p1", \
# 	"PY_DESC": "Test results of proportional brightening with correction for dark spots, alpha = 1.1"};
# results_path = "../rc_test/outputs/20170522_proportional_corrected_test_alpha1p1/"

# basic_info = {"PY_NAME": "prop_correct_ave_test_a1p1_perc5", \
# 	"PY_DESC": """Test results of proportional adjustment with correction for dark spots, alpha = 1.1,
# 	and obtaining target colour using brightest 5 percent of pixels"""};
# results_path = "../rc_test/outputs/20170524_prop_corr_1p1_ave_5/"

basic_info = {}
code_template_ref = ""
code_template_label = ""

# load "template" code for header
with open(frame_code_label_file) as f:    
    code_template_ref = f.read()

with open(frame_code_ref_file) as f:
	code_template_label = f.read()

originals_path = "../inputs/";
sequence = [{"PY_HAND_ORIG": "hand_dark", \
			"PY_HAND_TARG": "hand_brown", \
			"PY_HAND_RES": "hand_dark_to_hand_brown"}, \
			{"PY_HAND_ORIG": "hand_dark", \
			"PY_HAND_TARG": "hand_light", \
			"PY_HAND_RES": "hand_dark_to_hand_light"},
			{"PY_HAND_ORIG": "hand_dark", \
			"PY_HAND_TARG": "hand_pale", \
			"PY_HAND_RES": "hand_dark_to_hand_pale"},
			{"PY_HAND_ORIG": "hand_brown", \
			"PY_HAND_TARG": "hand_dark", \
			"PY_HAND_RES": "hand_brown_to_hand_dark"}, \
			{"PY_HAND_ORIG": "hand_brown", \
			"PY_HAND_TARG": "hand_light", \
			"PY_HAND_RES": "hand_brown_to_hand_light"},
			{"PY_HAND_ORIG": "hand_brown", \
			"PY_HAND_TARG": "hand_pale", \
			"PY_HAND_RES": "hand_brown_to_hand_pale"},
			{"PY_HAND_ORIG": "hand_light", \
			"PY_HAND_TARG": "hand_dark", \
			"PY_HAND_RES": "hand_light_to_hand_dark"}, \
			{"PY_HAND_ORIG": "hand_light", \
			"PY_HAND_TARG": "hand_brown", \
			"PY_HAND_RES": "hand_light_to_hand_brown"},
			{"PY_HAND_ORIG": "hand_light", \
			"PY_HAND_TARG": "hand_pale", \
			"PY_HAND_RES": "hand_light_to_hand_pale"},
			{"PY_HAND_ORIG": "hand_pale", \
			"PY_HAND_TARG": "hand_dark", \
			"PY_HAND_RES": "hand_pale_to_hand_dark"}, \
			{"PY_HAND_ORIG": "hand_pale", \
			"PY_HAND_TARG": "hand_brown", \
			"PY_HAND_RES": "hand_pale_to_hand_brown"},
			{"PY_HAND_ORIG": "hand_pale", \
			"PY_HAND_TARG": "hand_light", \
			"PY_HAND_RES": "hand_pale_to_hand_light"}]


def make_tex():
	# load "template" code for each row
	row_code_template = ""
	with open(row_code_file) as f:
		row_code_template = f.read()

	# add folder for row codes
	row_ref_folder = basic_info['PY_NAME'] + "_ref/"
	if not os.path.exists(row_ref_folder):
		os.makedirs(row_ref_folder)

	row_label_folder = basic_info['PY_NAME'] + "_label/"
	if not os.path.exists(row_label_folder):
		os.makedirs(row_label_folder)

	# add new row for each test
	row_label_content = ""
	row_ref_content = ""
	for test in sequence:
		row_code = row_code_template.replace("PY_HAND_ORIG", \
			originals_path + test['PY_HAND_ORIG'] + ".jpg")
		row_code = row_code.replace("PY_HAND_TARG", \
			originals_path + test['PY_HAND_TARG'] + ".jpg")
		row_code = row_code.replace("PY_HAND_RES", \
			results_path + test['PY_HAND_RES'] + ".jpg")
		row_code = row_code.replace("PY_HAND_RES", \
			results_path + test['PY_HAND_RES'] + ".jpg")
		row_code = row_code.replace("PY_ROW_NAME", test['PY_HAND_RES'])

		row_label_file_name = row_label_folder + test['PY_HAND_RES']
		with open(row_label_file_name + ".tex", "w") as f:
			f.write(row_code)

		row_label_content += "	\\input{" + "latex_maker/" + row_label_file_name + "}\n"
		row_label_content.replace('PY_NAME', basic_info['PY_NAME'])

		row_code_ref = row_code.replace("\\label", "\\ref")

		row_ref_file_name = row_ref_folder + test['PY_HAND_RES']
		with open(row_ref_file_name + ".tex", "w") as f:
			f.write(row_code_ref)

		row_ref_content += "	\\input{{" + "latex_maker/" + row_ref_file_name + "}}\n"
		row_ref_content.replace('PY_NAME', basic_info['PY_NAME'])

	code_label = code_template_label.replace("PY_INSERT_ROWS", row_label_content)
	code_ref = code_template_ref.replace("PY_INSERT_ROWS", row_ref_content)

	# fill in the basic info
	for key, value in basic_info.items():
	    code_label = code_label.replace(key, value)
	    code_ref = code_ref.replace(key, value)

	out_file_ref = basic_info['PY_NAME']+"-ref.tex"
	out_file_label = basic_info['PY_NAME']+"-label.tex"

	# output the finished tex file
	with open(out_file_label, "w") as f:  
	    f.write(code_label)

	with open(out_file_ref, "w") as f:  
	    f.write(code_ref)

print "Making latex..."
test_average_percs = [5, 10, 25, 100];
for perc in test_average_percs:
	basic_info = {"PY_NAME": "prop_correct_ave_test_a1p1_perc{}".format(str(perc)), \
	"PY_DESC": """Test results of proportional adjustment with correction for dark spots, alpha = 1.1,
	and obtaining target colour using brightest {} percent of pixels""".format(str(perc))};
	results_path = "../rc_test/outputs/20170524_prop_corr_1p1_ave_{}/".format(str(perc))

	make_tex()

print "Done."
