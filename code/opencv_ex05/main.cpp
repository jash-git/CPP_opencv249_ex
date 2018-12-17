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
	Mat src1, src2, dest;
	src1 = imread("LinuxLogo.jpg");
	src2 = imread("WindowsLogo.jpg");
    if (!src1.data) {
		printf("could not load LinuxLogo image...\n");
	}
	if (!src2.data) {
		printf("could not load win7logo image...\n");

	}
	if (src1.rows == src2.rows && src1.cols == src2.cols) {
		double alpha = 0.5;
		namedWindow("line-blend", CV_WINDOW_AUTOSIZE);
		addWeighted(src1, (1 - alpha), src2, alpha, 0.0, dest);
		imshow("line-blend", dest);
		waitKey(0);
	}
	else {
		printf("image size is not same...\n");
	}

    Pause();
    return 0;
}
