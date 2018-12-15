#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/ml/ml.hpp>

#include <iostream>
#include <cstdio>

#include <sys/timeb.h>
#if defined(WIN32)
    #define  TIMEB    _timeb
    #define  ftime    _ftime
    typedef __int64 TIME_T;
#else
    #define TIMEB timeb
    typedef long long TIME_T;
#endif

using namespace cv;
using namespace std;

void Pause()
{
    printf("Press Enter key to continue...");
    fgetc(stdin);
}
int main()
{
	Mat src00, dst00;
	Mat src01, dst01;
	src00 = imread("Lena_original.jpg");
	src01 = imread("Lena_original.jpg",IMREAD_GRAYSCALE);
	if (!src00.data) {
		printf("could not load image...\n");
	}
	else
    {
        namedWindow("input image00", CV_WINDOW_AUTOSIZE);
        imshow("input image00", src00);
        namedWindow("input image01", CV_WINDOW_AUTOSIZE);
        imshow("input image01", src01);

        Mat kernel = (Mat_<char>(3, 3) << 0, -1, 0, -1, 5, -1, 0, -1, 0);
        filter2D(src00, dst00, src00.depth(), kernel);
        filter2D(src01, dst01, src01.depth(), kernel);

        namedWindow("contrast image demo00", CV_WINDOW_AUTOSIZE);
        imshow("contrast image demo00", dst00);
        namedWindow("contrast image demo01", CV_WINDOW_AUTOSIZE);
        imshow("contrast image demo01", dst01);

        waitKey(0);

        cv::imwrite("contrast image demo00.png",dst00);
        cv::imwrite("contrast image demo01.png",dst01);
    }

	Pause();
    return 0;
}
