#include <iostream>
#include "opencv/cv.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"

#include "algo_piecewise.hpp"
#include "algo_linear.hpp"
#include "algo_darkspot_correct.hpp"

#include "algo_flags.hpp"

#include "utils.hpp"

using namespace std;
using namespace cv;

/**
 * modifies color of image, run for usage message
 */
int main( int argc, char** argv )
{
	String usage = "usage: recolor input_file_path param1 param2 param3 -mfile file_path_to_mask "
			"-ofile file_path_to_output -algo algorithm\n"
			"    input_file_path: path from current location to input image\n"
			"    param1: average B\n"
			"    param2: average G\n"
			"    param3: average R\n"
			"    file_path_to_mask (optional): path to the mask image, a black and white image"
					"showing which region of the input image to obtain the average color from.\n"
			"    file_path_to_output (optional): name and location to save the output image\n"
			"	 algorithm (optional): can be linear, pw or pw_dark_corr\n";
    if(argc < 5 || argc > 11){
    	printf("%s", usage.c_str()); cout.flush();
    	return 0;
    }

    /// Load the source image
    printf("DEBUG: image name %s\n", argv[1]);
    Mat src = imread( argv[1], IMREAD_COLOR); //reads 3 channel BGR

    // check input
    if(src.size().width <= 20 || src.size().height <= 20){
    	perror("ERROR: check input, image size should be at least 20 x 20 \n");
    	return 1;
    }

	printf("DEBUG: loaded image  w = %d h = %d\n", src.size().width, src.size().height); cout.flush();

    // Load input params
    Scalar input_params = Scalar(0.0, 0.0, 0.0);
    for(int i = 2; i < argc; i++){
    	input_params(i - 2) = atof(argv[i]);
    }

    // show input params
    printf("Input params b = %.2f, g = %.2f, r =%.2f\n", input_params(0), input_params(1), input_params(2)); cout.flush();

    // default algorithm
    int algo = PIECEWISE_DARKSPOT;

    // default no mask
    Mat average_col_mask;
    bool has_mask = false;

    // default output path
    string output_path = "outputs/out.jpg";
    string intermed_name = "outputs/out";
    bool has_outpath = false;

    // get optional arguments if provided
    for(int i = 5; i < argc - 1; i++){
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
        if(strcmp(argv[i], "-mfile") == 0){
        	printf("DEBUG: mask name %s\n", argv[i + 1]);
        	average_col_mask = imread(argv[i + 1], IMREAD_GRAYSCALE);

        	if(average_col_mask.size().width != src.size().width || average_col_mask.size().height != src.size().height){
        		perror("ERROR: check input, mask size doesn't match image size\n");
            	return 1;
            }

        	printf("DEBUG: loaded image mask w = %d h = %d\n", average_col_mask.size().width, average_col_mask.size().height); cout.flush();
        	has_mask = true;
        }

        // get the output path if provided
        if(strcmp(argv[i], "-ofile") == 0){

        	output_path = string(argv[i + 1]);
        	printf("DEBUG: got out path %s\n", output_path.c_str()); cout.flush();

        	intermed_name = remove_extension(output_path);
        	printf("DEBUG: got intermediate name %s\n", intermed_name.c_str()); cout.flush();

        	has_outpath = true;
        }
    }

    // average colours
    Scalar target = Scalar(input_params(0), input_params(1), input_params(2));
    Scalar average;
    if(has_mask){
    	average = mean(src, average_col_mask);
    } else {
		Mat average_roi = src( Rect(src.rows/2 - 5,src.rows/2 + 5,10,10) );
		average = mean(average_roi);
	}
    printf("DEBUG: image average b = %.2f, g = %.2f, r =%.2f\n", average(0), average(1), average(2)); cout.flush();

    // process
    Mat dst = Mat::zeros( src.size(), src.type());

    if(algo == LINEAR){
    	linear_process(src, dst, target, average);
    } else if(algo == PIECEWISE){
    	piecewise_process(src, dst, target, average);
    } else if(algo == PIECEWISE_DARKSPOT){
    	piecewise_process(src, dst, target, average);
        //DEBUG draw intermediate
        imwrite(intermed_name + "-pw_intermediate.jpg", dst);

        // Get average colour again
        if(has_mask){
        	average = mean(dst, average_col_mask);
        } else {
    		Mat average_roi = dst( Rect(dst.rows/2 - 5,dst.rows/2 + 5,10,10) );
    		average = mean(average_roi);
    	}
        printf("DEBUG: new image average b = %.2f, g = %.2f, r =%.2f\n", average(0), average(1), average(2)); cout.flush();

    	darkcorrect_process(dst, dst, average, 3.0); //using target colour as new average colour
    }

    //DEBUG, draw average colors
    rectangle(dst, Point(dst.cols - 7, dst.rows - 14), Point(dst.cols - 2, dst.rows - 9), average, CV_FILLED);
    rectangle(dst, Point(dst.cols - 7, dst.rows - 7), Point(dst.cols - 2, dst.rows - 2), target, CV_FILLED);

    // print output
    imwrite(output_path, dst);

    printf("Recolor done.\n"); cout.flush();

    return 0;
}
