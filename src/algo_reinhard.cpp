/*
 * algo_reinhard.cpp
 *
 *  Created on: Jun 17, 2017
 *      Author: tina
 */
#include "algo_reinhard.hpp"

using namespace std;
using namespace cv;


int reinhard_process(cv::Mat src, cv::Mat dst){
	printf("piecewise_process... ");

	//Mat lab;
	cvtColor(src, dst, CV_BGR2Lab);
	//imwrite("outputs/lab.jpg", dst);


	return 0;
}

