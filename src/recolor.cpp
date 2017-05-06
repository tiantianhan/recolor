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
    /// Load the source image
    Mat src = imread( argv[1], IMREAD_COLOR);

	String usage = "usage: recolor input_file_path param1 param2 param3\n"
			"    input_file_path: path from current location to input image\n"
			"    param1: average R\n"
			"    param2: average G\n"
			"    param3: average B\n"
			"    output: saves output image to output folder\n";
    if(argc < 4){
    	printf("%s", usage.c_str()); cout.flush();
    	return 0;
    }

    //input params
    Scalar input_params = Scalar(0.0, 0.0, 0.0);
    for(int i = 2; i < argc; i++){
    	input_params(i - 2) = atof(argv[i]);
    }

    // check input
    if(src.size().width <= 0 || src.size().height <= 0){
    	perror("ERROR: check input, image size < 0");
    	return 1;
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
    Mat average_roi = src( Rect(src.rows/2 - 5,src.rows/2 + 5,10,10) );
    Scalar average = cv::mean(average_roi);
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

    // print output
    imwrite("outputs/small_range.jpg", dst);

    return 0;
}
