/*
 * algo_piecewise.cpp
 *
 *  Created on: May 9, 2017
 *      Author: tina
 */

#include <iostream>
#include "opencv/cv.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "algo_piecewise.hpp"

using namespace std;
using namespace cv;

int piecewise_process(Mat src, Mat dst, Scalar target, Scalar average){
	 printf("Applying piecewise process...\n"); cout.flush();

    // process
    double src_col = 0.0;
    double dst_col = 0.0;
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

    return 0;
}
