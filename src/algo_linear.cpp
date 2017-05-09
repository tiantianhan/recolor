/*
 * algo_linear.cpp
 *
 *  Created on: May 9, 2017
 *      Author: tina
 */

#include "algo_linear.hpp"

using namespace std;
using namespace cv;

int linear_process(Mat src, Mat dst, Scalar target, Scalar average){
    printf("Applying linear process...\n"); cout.flush();

    // process
	Scalar difference = target - average;
    printf("DEBUG: color difference b = %.2f, g = %.2f, r =%.2f\n", difference(0), difference(1), difference(2)); cout.flush();

    double src_col = 0.0;
    double dst_col = 0.0;
    for(int y = 0; y < src.rows; y++){
    	for(int x = 0; x < src.cols; x++){
    		for(int c = 0; c < 3; c++){
    			src_col = src.at<Vec3b>(y,x)[c];

    			dst_col = src_col + difference(c);

    			dst.at<Vec3b>(y,x)[c] = saturate_cast<uchar>(dst_col);
    		}
    	}
    }

    return 0;
}
