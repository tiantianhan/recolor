/*
 * algo_average_col.hpp
 *
 *  Created on: May 23, 2017
 *      Author: tina
 */

#ifndef ALGO_AVERAGE_COL_HPP_
#define ALGO_AVERAGE_COL_HPP_
#include <iostream>
#include "opencv/cv.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"

cv::Scalar average_brightest(cv::Mat image, cv::Mat mask, double fraction);


#endif /* ALGO_AVERAGE_COL_HPP_ */
