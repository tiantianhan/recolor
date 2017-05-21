#include <iostream>
#include "opencv/cv.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"

#include "algo_piecewise.hpp"
#include "algo_linear.hpp"
#include "algo_darkspot_correct.hpp"
#include "recolor_flags.hpp"

#include "utils.hpp"

using namespace std;
using namespace cv;

/**
 * modifies color of image, run for usage message
 */
int main( int argc, char** argv )
{
	String usage = "usage: recolor input_file_path target_file_path "
			"-d "
			"-inmask file_path_to_input_mask "
			"-targmask file_path_to_target_mask "
			"-ofile file_path_to_output "
			"-algo algorithm "
			"-alpha alpha\n"
			"    input_file_path: path from current location to input image\n"
			"    target_file_path: path from current location to target image\n"
			"    -d  use flag to indicate debug mode\n"
			"    file_path_to_input_mask (optional): path to the mask image, a black and white image"
					"showing which region of the input image to obtain the average color from."
					"If not provided a region at the center of the image will be used.\n"
			"    file_path_to_input_mask (optional): path to the mask image, a black and white image"
					"showing which region of the input image to obtain the average color from."
					"If not provided a region at the center of the image will be used.\n"
			"    file_path_to_output (optional): name and location to save the output image. "
					"Otherwise saved in default outputs/ folder \n"
			"    algorithm (optional): can be linear, pw or pw_dark_corr."
					"If not give or name is invalid pw_dark_corr is used by default\n"
			"    alpha (optional): only used for pw_dark_corr algorithm, the alpha value for the correction\n";

	if(argc < MIN_ARGS || argc > MAX_ARGS){
    	printf("%s", usage.c_str()); cout.flush();
    	return 0;
    }

    /// Load the source image
    printf("Loading input image %s...\n", argv[1]);
    Mat src = imread( argv[1], IMREAD_COLOR); //reads 3 channel BGR

    // check input
    if(src.size().width <= 20 || src.size().height <= 20){
    	perror("ERROR: check input, image size should be at least 20 x 20 \n");
    	return 1;
    }

	printf("Loaded input image  w = %d h = %d\n", src.size().width, src.size().height); cout.flush();

    // Load the target image
    printf("Loading target image %s...\n", argv[2]);
    Mat targ = imread( argv[2], IMREAD_COLOR); //reads 3 channel BGR

    // check input
    if(targ.size().width <= 20 || targ.size().height <= 20){
    	perror("ERROR: check input, image size should be at least 20 x 20 \n");
    	return 1;
    }

	printf("Loaded target image  w = %d h = %d\n", targ.size().width, targ.size().height); cout.flush();

	// default is not debug
	bool is_debug = false;

	// default algorithm
    int algo = ALGO_DEFAULT;

    // default no mask
    Mat in_ave_col_mask;
    Mat targ_ave_col_mask;
    bool has_in_mask = false;
    bool has_targ_mask = false;

    // default output path
    string output_path = "outputs/out.jpg";
    string intermed_name = "outputs/out";
    bool has_outpath = false;

    // default alpha
    double alpha = ALPHA_DEFAULT;

    // get optional flags without arguments
    for(int i = MIN_ARGS; i < argc; i++){
    	if(strcmp(argv[i], "-d") == 0){
    		is_debug = true;
    	}
    }

    // get optional arguments
    for(int i = MIN_ARGS; i < argc - 1; i++){

    	if(strcmp(argv[i], "-algo") == 0){
    		if(strcmp(argv[i + 1], "linear") == 0){
    			algo = LINEAR;
    			printf("Using algorithm %s\n", "Linear"); cout.flush();

    		} else if(strcmp(argv[i + 1], "pw") == 0){
    			algo = PIECEWISE;
    			printf("Using algorithm %s\n", "Piecewise"); cout.flush();

    		} else if(strcmp(argv[i + 1], "pw_dark_corr") == 0){
    			algo = PIECEWISE_DARKSPOT;
    			printf("Using algorithm %s\n", "Piecewise + dark correction"); cout.flush();

    		} else {
    			perror("WARNING: invalid algorithm name, using default\n");
    		}
    	}

    	// get average color mask for input if provided
        if(strcmp(argv[i], "-inmask") == 0){
        	printf("Loading input mask %s...\n", argv[i + 1]);
        	in_ave_col_mask = imread(argv[i + 1], IMREAD_GRAYSCALE);

        	if(in_ave_col_mask.size().width != src.size().width || in_ave_col_mask.size().height != src.size().height){
        		perror("ERROR: check input, mask size doesn't match image size\n");
            	return 1;
            }

        	printf("Loaded input mask w = %d h = %d\n", in_ave_col_mask.size().width, in_ave_col_mask.size().height); cout.flush();
        	has_in_mask = true;
        }

    	// get average color mask for target if provided
        if(strcmp(argv[i], "-targmask") == 0){
        	printf("Loading target mask %s...\n", argv[i + 1]);
        	targ_ave_col_mask = imread(argv[i + 1], IMREAD_GRAYSCALE);

        	if(targ_ave_col_mask.size().width != targ.size().width || targ_ave_col_mask.size().height != targ.size().height){
        		perror("ERROR: check input, mask size doesn't match image size\n");
            	return 1;
            }

        	printf("Loaded target mask w = %d h = %d\n", targ_ave_col_mask.size().width, targ_ave_col_mask.size().height); cout.flush();
        	has_targ_mask = true;
        }

        // get the output path if provided
        if(strcmp(argv[i], "-ofile") == 0){

        	output_path = string(argv[i + 1]);
        	printf("Set out path as %s\n", output_path.c_str()); cout.flush();

        	intermed_name = remove_extension(output_path);
        	if(is_debug){
        		printf("DEBUG: got intermediate name %s\n", intermed_name.c_str()); cout.flush();
        	}

        	has_outpath = true;
        }

        if(strcmp(argv[i], "-alpha") == 0){
        	// Load input params
        	alpha = atof(argv[i+1]);

			// show input params
			printf("Set alpha = %f\n", alpha); cout.flush();
        }
    }

    // average colours
    Scalar target;
    if(has_targ_mask){
    	target = mean(targ, targ_ave_col_mask);
    } else {
		Mat average_roi = src( Rect(targ.rows/2 - 5, targ.rows/2 + 5,10,10) );
		target = mean(average_roi);
    }
    printf("Target image average b = %.2f, g = %.2f, r =%.2f\n", target(0), target(1), target(2)); cout.flush();

    Scalar average;
    if(has_in_mask){
    	average = mean(src, in_ave_col_mask);
    } else {
		Mat average_roi = src( Rect(src.rows/2 - 5,src.rows/2 + 5,10,10) );
		average = mean(average_roi);
	}
    printf("Input image average b = %.2f, g = %.2f, r =%.2f\n", average(0), average(1), average(2)); cout.flush();

    // process
    Mat dst = Mat::zeros( src.size(), src.type());

    if(algo == LINEAR){
    	linear_process(src, dst, target, average);
    } else if(algo == PIECEWISE){
    	piecewise_process(src, dst, target, average);
    } else if(algo == PIECEWISE_DARKSPOT){
    	piecewise_process(src, dst, target, average);
        //DEBUG draw intermediate
    	if(is_debug){
    		string intermed_file_name = intermed_name + "-pw_intermediate.jpg";
			printf("DEBUG: writing intermediate to %s...\n", intermed_file_name.c_str()); cout.flush();
			imwrite(intermed_file_name, dst);
    	}

        // Get average colour again
        if(has_in_mask){
        	average = mean(dst, in_ave_col_mask);
        } else {
    		Mat average_roi = dst( Rect(dst.rows/2 - 5,dst.rows/2 + 5,10,10) );
    		average = mean(average_roi);
    	}

        if(is_debug){
        	printf("DEBUG: new image average b = %.2f, g = %.2f, r =%.2f\n", average(0), average(1), average(2)); cout.flush();
        }

    	darkcorrect_process(dst, dst, average, alpha); //using target colour as new average colour
    }

    if(is_debug){
    	//DEBUG, draw average colors
    	rectangle(dst, Point(dst.cols - 7, dst.rows - 14), Point(dst.cols - 2, dst.rows - 9), average, CV_FILLED);
    	rectangle(dst, Point(dst.cols - 7, dst.rows - 7), Point(dst.cols - 2, dst.rows - 2), target, CV_FILLED);
    }

    // print output
    imwrite(output_path, dst);

    printf("Recolor done.\n"); cout.flush();

    return 0;
}
