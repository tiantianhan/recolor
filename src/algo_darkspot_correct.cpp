/*
 * algo_darkspot_correct.cpp
 *
 *  Created on: May 12, 2017
 *      Author: tina
 */

#include "algo_darkspot_correct.hpp"

using namespace std;
using namespace cv;

int darkcorrect_process(Mat src, Mat dst, Scalar average, double alpha){
	 printf("Applying darkspot correct process...\n"); cout.flush();
	 printf("Average b = %f, g = %f, r = %f, Alpha = %f\n", average(0), average(1), average(2), alpha); cout.flush();

	    // process
	    double src_col = 0.0;
	    double dst_col = 0.0;
	    for(int y = 0; y < src.rows; y++){
	    	for(int x = 0; x < src.cols; x++){
	    		for(int c = 0; c < 3; c++){
	    			src_col = src.at<Vec3b>(y,x)[c];
	    			if(src_col < average(c)){
	    				dst_col = average(c) - (average(c) - src_col) / alpha;
	    				dst.at<Vec3b>(y,x)[c] = dst_col;
	    			}
	    		}
	    	}
	    }

    return 0;
}



