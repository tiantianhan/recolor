#include <iostream>
#include "opencv/cv.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"

using namespace std;
using namespace cv;

Mat src; Mat dst;
char window_name1[] = "Unprocessed Image";
char window_name2[] = "Processed Image";

int main( int argc, char** argv )
{
    /// Load the source image
    src = imread( argv[1], 1 );

    //target rgb
    Vec3b target_col = Vec3b(255, 0, 0);

    // check input
    if(src.size().width <= 0 || src.size().height <= 0){
    	perror("ERROR: check input, image size < 0");
    	return 1;
    }

    for(int c = 0; c < 3; c++){
		if(target_col(c) < 0 || target_col(c) > 255){
			perror("ERROR: check input, strange value for target color");
			return 1;
		}
    }

    // show input
    namedWindow( window_name1, WINDOW_NORMAL );
    imshow("Unprocessed Image",src);
    printf("Target Color R, G, B = %d, %d, %d\n", target_col(0), target_col(1), target_col(2)); cout.flush();

    // calculation
    double target_avg = 1.0/3.0 * (target_col(0) + target_col(1) + target_col(2));
    printf("DEBUG: target_avg = %f\n", target_avg); cout.flush();
    double alpha = 1.0;
    double beta = 100.0;

    // process
    Mat dst = Mat::zeros( src.size(), src.type());
    for(int y = 0; y < src.rows; y++){
    	for(int x = 0; x < src.cols; x++){
    		for(int c = 0; c < 3; c++){
    			dst.at<Vec3b>(y,x)[c] = saturate_cast<uchar>( alpha*( src.at<Vec3b>(y,x)[c] ) + beta );
    		}
    	}
    }

    // show output
    namedWindow( window_name2, WINDOW_NORMAL );
    imshow("Processed Image",dst);

    waitKey();

    return 0;
}
