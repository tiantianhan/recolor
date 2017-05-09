/*
 * algo_piecewise.hpp
 *
 *  Created on: May 9, 2017
 *      Author: tina
 */

#ifndef ALGO_PIECEWISE_HPP_
#define ALGO_PIECEWISE_HPP_

#include <iostream>
#include "opencv/cv.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"

using namespace std;
using namespace cv;

int piecewise_process(Mat src, Mat dst, Scalar target, Scalar average);

#endif /* ALGO_PIECEWISE_HPP_ */
