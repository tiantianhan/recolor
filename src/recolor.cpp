#include <iostream>
#include "opencv/cv.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"

#include "algo_piecewise.hpp"
#include "algo_linear.hpp"
#include "algo_darkspot_correct.hpp"

using namespace std;
using namespace cv;

/**
 * modifies color of image, run for usage message
 */
int main( int argc, char** argv )
{
	String usage = "usage: recolor input_file_path param1 param2 param3 file_path_to_mask\n"
			"    input_file_path: path from current location to input image\n"
			"    param1: average B\n"
			"    param2: average G\n"
			"    param3: average R\n"
			"    file_path_to_mask (optional): path to the mask image, a black and white image"
					"showing which region of the input image to obtain the average color from.\n"
			"    output: saves output image to outputs folder\n";
    if(argc < 5){
    	printf("%s", usage.c_str()); cout.flush();
    	return 0;
    }

    //input params
    Scalar input_params = Scalar(0.0, 0.0, 0.0);
    for(int i = 2; i < argc; i++){
    	input_params(i - 2) = atof(argv[i]);
    }

    /// Load the source image
    printf("DEBUG: image name name %s\n", argv[1]);
    Mat src = imread( argv[1], IMREAD_COLOR); //reads 3 channel BGR

    // check input
    if(src.size().width <= 20 || src.size().height <= 20){
    	perror("ERROR: check input, image size should be at least 20 x 20 \n");
    	return 1;
    }

	printf("DEBUG: loaded image  w = %d h = %d\n", src.size().width, src.size().height); cout.flush();

    // get mask if provided
    Mat average_col_mask;
    bool has_mask = false;
    if(argc >= 6){
    	printf("DEBUG: mask name %s\n", argv[5]);
    	average_col_mask = imread(argv[5], IMREAD_GRAYSCALE);

    	if(average_col_mask.size().width != src.size().width || average_col_mask.size().height != src.size().height){
    		perror("ERROR: check input, mask size doesn't match image size\n");
        	return 1;
        }

    	printf("DEBUG: loaded image mask w = %d h = %d\n", average_col_mask.size().width, average_col_mask.size().height); cout.flush();
    	has_mask = true;
    }

    // show input
    printf("Input params b = %.2f, g = %.2f, r =%.2f\n", input_params(0), input_params(1), input_params(2)); cout.flush();

    // calculations
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
    piecewise_process(src, dst, target, average);
    //linear_process(src, dst, target, average);
    //DEBUG draw intermediate
    imwrite("outputs/pw_intermediate.jpg", dst);

    darkcorrect_process(dst, dst, target, 5.0); //using target colour as new average colour

    //DEBUG, draw average colors
    rectangle(dst, Point(dst.cols - 7, dst.rows - 14), Point(dst.cols - 2, dst.rows - 9), average, CV_FILLED);
    rectangle(dst, Point(dst.cols - 7, dst.rows - 7), Point(dst.cols - 2, dst.rows - 2), target, CV_FILLED);

    // print output
    imwrite("outputs/output.jpg", dst);

    return 0;
}
