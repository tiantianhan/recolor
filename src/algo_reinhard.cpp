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
	printf("piecewise_process... \n");

	Mat src_lab, targ_lab, srcf, targf, dstf;
	Scalar src_lab_mean, src_lab_stdev, targ_lab_mean, targ_lab_stdev;

	src.convertTo(srcf, CV_32FC3, 1/255.0);
	targ.convertTo(targf, CV_32FC3, 1/255.0);

	cvtColor(srcf, src_lab, CV_BGR2Lab);
	cvtColor(targf, targ_lab, CV_BGR2Lab);

	imwrite("outputs/src_lab.jpg", src_lab);
	imwrite("outputs/targ_lab.jpg", targ_lab);

	meanStdDev(src_lab, src_lab_mean, src_lab_stdev, src_mask);
	meanStdDev(targ_lab, targ_lab_mean, targ_lab_stdev, targ_mask);

	printf("got starting averages lab: %f %f %f\n ", src_lab_mean(0), src_lab_mean(1), src_lab_mean(2));
	printf("got target averages lab: %f %f %f\n ", targ_lab_mean(0), targ_lab_mean(1), targ_lab_mean(2));


	subtract(src_lab, src_lab_mean, dstf);
	divide(dstf, src_lab_stdev, dstf);
	multiply(dstf, targ_lab_stdev, dstf);
	add(dstf, targ_lab_mean, dstf);

	Scalar dst_mean, dst_stdev;
	Scalar dst_meanf, dst_stdevf;
	meanStdDev(dstf, dst_meanf, dst_stdevf, src_mask);
	printf("got result averages lab: %f %f %f\n ", dst_meanf(0), dst_meanf(1), dst_meanf(2));

	cvtColor(dstf, dstf, CV_Lab2BGR);
	dstf.convertTo(dst, CV_8UC3, 255.0);

	meanStdDev(dstf, dst_meanf, dst_stdevf, src_mask);
	meanStdDev(dst, dst_mean, dst_stdev, src_mask);

	printf("got result averages bgr: %f %f %f\n ", dst_meanf(0), dst_meanf(1), dst_meanf(2));
	printf("got result averages bgr: %f %f %f\n ", dst_mean(0), dst_mean(1), dst_mean(2));
	return 0;
}

