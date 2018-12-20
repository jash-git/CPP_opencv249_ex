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
Mat src;//input image
void Pause()
{
    printf("Press Enter key to continue...");
    fgetc(stdin);
}
int main()
{
	src = imread("bgImage.jpg");
	if (!src.data)
    {
		printf("could not load image...\n");
	}
    else
    {
        Mat gblur;
        Mat blur;
        namedWindow("Lena_original", CV_WINDOW_AUTOSIZE);
        imshow("Lena_original", src);

        char output_title00[] = "blur image";
        namedWindow(output_title00, CV_WINDOW_AUTOSIZE);
        cv::blur(src, blur, Size(11, 11), Point(-1, -1));
        imshow(output_title00, blur);

        char output_title01[] = "gaussian blur";
        GaussianBlur(src, gblur, Size(11, 11), 11, 11);
        namedWindow(output_title01, CV_WINDOW_AUTOSIZE);
        imshow(output_title01, gblur);

    }
    waitKey(0);
    return 0;
}
