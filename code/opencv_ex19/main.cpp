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

int t1_value = 50;
int max_value = 255;
Mat gray_src;
const char* OUTPUT_TITLE = "Canny Result";
void Canny_Demo(int, void*);

int main()
{
    Mat input;
	input = imread("Lena_original.jpg");
	if (!input.data)
    {
		printf("could not load image...\n");
	}
    else
    {
        //放大
        pyrUp(input, src, Size(input.cols*2, input.rows*2));

        Mat tmp;
        GaussianBlur(src, tmp, Size(3, 3), 0, 0);//高斯模糊GaussianBlur目的為了給圖像預處理時候減低噪聲(雜訊)
        cvtColor(tmp, gray_src, CV_BGR2GRAY);//彩色轉灰階
        imshow("Lena_gray", gray_src);

        namedWindow(OUTPUT_TITLE, CV_WINDOW_AUTOSIZE);
        createTrackbar("Threshold Value:", OUTPUT_TITLE, &t1_value, max_value, Canny_Demo);
        Canny_Demo(0, 0);
    }
    waitKey(0);
    Pause();
    return 0;
}
void Canny_Demo(int, void*) {
	Mat edge_output;
	Canny(gray_src, edge_output, t1_value, t1_value * 2, 3, false);

	imshow(OUTPUT_TITLE, ~edge_output);
}
