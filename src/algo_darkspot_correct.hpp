/*
 * algo_darkspot_correct.hpp
 *
 *  Created on: May 12, 2017
 *      Author: tina
 */

#ifndef ALGO_DARKSPOT_CORRECT_HPP_
#define ALGO_DARKSPOT_CORRECT_HPP_

#include <iostream>
#include "opencv/cv.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"

using namespace std;
using namespace cv;

/*
 * Removes dark spots from hand, strength of effect controlled by alpha, alpha > 1
 */
int darkcorrect_process(Mat src, Mat dst, Scalar average, double alpha);


#endif /* ALGO_DARKSPOT_CORRECT_HPP_ */
