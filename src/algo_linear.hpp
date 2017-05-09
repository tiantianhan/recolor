/*
 * algo_linear.hpp
 *
 *  Created on: May 9, 2017
 *      Author: tina
 */

#ifndef ALGO_LINEAR_HPP_
#define ALGO_LINEAR_HPP_

#include <iostream>
#include "opencv/cv.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"

using namespace std;
using namespace cv;

int linear_process(Mat src, Mat dst, Scalar target, Scalar average);
#endif /* ALGO_LINEAR_HPP_ */
