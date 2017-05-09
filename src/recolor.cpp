#include <iostream>
#include "opencv/cv.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"

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
			"    param4: file_path_to_mask (optional)\n"
			"    output: saves output image to output folder\n";
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

    /*double alpha = input_params(0);
    double beta = input_params(1);

    if(alpha <= 0 || alpha > 10.0){
		perror("ERROR: check input, strange value for input params");
		return 1;
    }

    if(beta < -255 || beta > 255){
		perror("ERROR: check input, strange value for input params");
		return 1;
    }*/

    // show input
    printf("Input params b = %.2f, g = %.2f, r =%.2f\n", input_params(0), input_params(1), input_params(2)); cout.flush();
//    printf("Input params alpha = %.2f, beta = %.2f\n", alpha, beta); cout.flush();

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
    double src_col = 0.0;
    double dst_col = 0.0;
    Mat dst = Mat::zeros( src.size(), src.type());
    for(int y = 0; y < src.rows; y++){
    	for(int x = 0; x < src.cols; x++){
    		for(int c = 0; c < 3; c++){
    			src_col = src.at<Vec3b>(y,x)[c];
    			if(src_col > average(c)){
    				dst_col = 255.0 - ((255.0 - src_col) * (255.0 - target(c)) / (255.0 - average(c)));
    				//printf("DEBUG: srccolor %f dstcolor %f ", src_col, dst_col); cout.flush();

    			} else {
    				dst_col = src_col * (target(c) / average(c));
    			}

    			dst.at<Vec3b>(y,x)[c] = dst_col;
    		}
    	}
    }

    //DEBUG, draw average colors
    rectangle(dst, Point(dst.cols - 7, dst.rows - 14), Point(dst.cols - 2, dst.rows - 9), average, CV_FILLED);
    rectangle(dst, Point(dst.cols - 7, dst.rows - 7), Point(dst.cols - 2, dst.rows - 2), target, CV_FILLED);

    // print output
    imwrite("outputs/output.jpg", dst);

    //DEBUG
    if(has_mask){
    	imwrite("outputs/got_mask.jpg", average_col_mask);
    }

    return 0;
}
