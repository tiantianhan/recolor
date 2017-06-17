/*
 * algo_reinhard.hpp
 *
 *  Created on: Jun 17, 2017
 *      Author: tina
 */

#ifndef ALGO_REINHARD_HPP_
#define ALGO_REINHARD_HPP_

#include <iostream>
#include "opencv/cv.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "algo_piecewise.hpp"

int reinhard_process(cv::Mat src, cv::Mat targ, cv::Mat src_mask, cv::Mat targ_mask, cv::Mat dst);


#endif /* ALGO_REINHARD_HPP_ */
