
import os

frame_code_file = "frame_code.txt" # txt file containing the latex code for table
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

basic_info = {"PY_NAME": "prop_correct_test_a3", \
	"PY_DESC": "Test results of proportional brightening with correction for dark spots, alpha = 3"};
results_path = "../rc_test/outputs/20170517_proportional_corrected_test_alpha3/"

out_file = basic_info['PY_NAME']+"-summary.tex"
code = ""

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


# load "template" code for header
with open(frame_code_file) as f:    
    code = f.read()

# load "template" code for each row
row_code_template = ""
with open(row_code_file) as f:
	row_code_template = f.read()

# add new row for each test
row_content = ""
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
	row_content += row_code

code = code.replace("PY_INSERT_ROWS", row_content)

# fill in the basic info
for key, value in basic_info.items():
    code = code.replace(key, value)

# output the finished tex file
with open(out_file, "w") as f:  
    f.write(code)

