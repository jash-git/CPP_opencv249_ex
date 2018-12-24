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
	src = imread("Lena_original.jpg");
	if (!src.data)
    {
		printf("could not load image...\n");
	}
    else
    {
        namedWindow("color_input", CV_WINDOW_AUTOSIZE);
        imshow("color_input", src);

        Mat s_up;
        //放大
        pyrUp(src, s_up, Size(src.cols*2, src.rows * 2));
        imshow("zoom in", s_up);

        //縮小
        Mat s_down;
        pyrDown(src, s_down, Size(src.cols / 2, src.rows / 2));
        imshow("zoom out", s_down);

        //高斯平滑濾波
        Mat gray_src, g1, g2, dogImg;
        cvtColor(s_up, gray_src, CV_BGR2GRAY);
        GaussianBlur(gray_src, g1, Size(5, 5), 0, 0);
        GaussianBlur(g1, g2, Size(5, 5), 0, 0);
        //圖像相減
        subtract(g1, g2, dogImg, Mat());

        //圖像歸一化顯示
        normalize(dogImg, dogImg, 255, 0, NORM_MINMAX);
        imshow("DOG Image", dogImg);
    }
    waitKey(0);
    Pause();
    return 0;
}
