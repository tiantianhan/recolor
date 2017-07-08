/*
 * algo_average_col.cpp
 *
 *  Created on: May 23, 2017
 *      Author: tina
 */


#include "algo_average_col.hpp"

using namespace cv;
using namespace std;

//helpers
double percentile(Mat channel, Mat mask, double perc);

Scalar average_brightest(Mat image, Mat mask, double fraction){
	printf("Finding average of brightest %f fraction...\n", fraction); cout.flush();

	// find percentile color
	Mat grey;
	cvtColor(image, grey, CV_BGR2GRAY);
	double perc_col = percentile(grey, mask, (1.0 - fraction));

	printf("Got percentile color = %f\n", perc_col); cout.flush();

	// find mask of pixels above percentile
	//threshold( src_gray, dst, threshold_value, max_BINARY_value,threshold_type );
	Mat brightest_mask;
	threshold(grey, brightest_mask, perc_col, 255, THRESH_BINARY);

	// merge the two masks
	Mat result_mask;
	bitwise_and(brightest_mask,mask,result_mask);

	//DEBUG
	printf("DEBUG: printing new masks...\n"); cout.flush();
	imwrite("outputs/adjusted_mask.jpg", result_mask);


	Scalar result = mean(image, result_mask);
	return result;
}


// calculates the color at a given percentile (median = 0.5) of a 1 channel image
// based on https://gist.github.com/heisters/9cd68181397fbd35031b
double percentile(Mat channel, Mat mask, double perc)
{
    double m = countNonZero(mask) * perc;
    int bin = 0;
    double med = -1.0;

    int histSize = 256;
    float range[] = { 0, 256 };
    const float* histRange = { range };
    bool uniform = true;
    bool accumulate = false;
    cv::Mat hist;
    cv::calcHist( &channel, 1, 0, mask, hist, 1, &histSize, &histRange, uniform, accumulate );
    //printf("Finding median... hist size %d, half num pix %f\n", histSize, m); cout.flush();

    for ( int i = 0; i < histSize && med < 0.0; ++i )
    {
        bin += cvRound( hist.at< float >( i ) );
        //printf("%d bin no %d\n", i, bin); cout.flush();
        if ( bin > m && med < 0.0 ){
            med = i;
            //printf("%d set med %f\n", i, med); cout.flush();
        }
    }

    //printf("got med %f\n", med); cout.flush();

    return med;
}
