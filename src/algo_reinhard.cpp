/*
 * algo_reinhard.cpp
 *
 *  Created on: Jun 17, 2017
 *      Author: tina
 */
#include "algo_reinhard.hpp"

using namespace std;
using namespace cv;


int reinhard_process(cv::Mat src, cv::Mat targ, cv::Mat src_mask, cv::Mat targ_mask, cv::Mat dst){
	printf("piecewise_process... ");

	Mat src_lab, targ_lab;
	Scalar src_lab_mean, src_lab_stdev, targ_lab_mean, targ_lab_stdev;

	cvtColor(src, src_lab, CV_BGR2Lab);
	cvtColor(targ, targ_lab, CV_BGR2Lab);

	imwrite("outputs/src_lab.jpg", src_lab);
	imwrite("outputs/targ_lab.jpg", targ_lab);

	meanStdDev(src_lab, src_lab_mean, src_lab_stdev, src_mask);
	meanStdDev(targ_lab, targ_lab_mean, targ_lab_stdev, targ_mask);

	subtract(src_lab, src_lab_mean, dst);
	divide(dst, src_lab_stdev, dst);
	multiply(dst, targ_lab_stdev, dst);
	add(dst, targ_lab_mean, dst);

	cvtColor(dst, dst, CV_Lab2BGR);
	return 0;
}

