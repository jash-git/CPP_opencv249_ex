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
Mat src2;
Mat dst01,dst02;
char OUTPUT_WIN01[] = "output-dilate";
char OUTPUT_WIN02[] = "output-erode";
int element_size = 3;
int max_size = 21;
void CallBack_Demo01(int, void*);
void CallBack_Demo02(int, void*);
void Pause()
{
    printf("Press Enter key to continue...");
    fgetc(stdin);
}
int main()
{
	src = imread("bgImage.jpg",IMREAD_GRAYSCALE);
	if (!src.data)
    {
		printf("could not load image...\n");
	}
    else
    {

        threshold(src,src2,120,255,THRESH_BINARY);//設定門閥值灰階轉二值化 < 120->0,>120->255
        namedWindow("Lena_original", CV_WINDOW_AUTOSIZE);
        imshow("Lena_original", src);
        namedWindow("Lena_BINARY", CV_WINDOW_AUTOSIZE);
        imshow("Lena_BINARY", src2);
        namedWindow(OUTPUT_WIN01, CV_WINDOW_AUTOSIZE);
        createTrackbar("Element Size :", OUTPUT_WIN01, &element_size, max_size, CallBack_Demo01);
        CallBack_Demo01(0, 0);
        namedWindow(OUTPUT_WIN02, CV_WINDOW_AUTOSIZE);
        createTrackbar("Element Size :", OUTPUT_WIN02, &element_size, max_size, CallBack_Demo02);
        CallBack_Demo02(0, 0);

    }
    waitKey(0);
    return 0;
}
void CallBack_Demo01(int, void*) {
	int s = element_size * 2 + 1;
	Mat structureElement = getStructuringElement(MORPH_RECT, Size(s, s), Point(-1, -1));
	dilate(src2, dst01, structureElement, Point(-1, -1), 1);//膨脹->白色越多

	imshow(OUTPUT_WIN01, dst01);
	return;
}
void CallBack_Demo02(int, void*) {
	int s = element_size * 2 + 1;
	Mat structureElement = getStructuringElement(MORPH_RECT, Size(s, s), Point(-1, -1));
    erode(src2, dst02, structureElement);//腐蝕->黑色越多

	imshow(OUTPUT_WIN02, dst02);
	return;
}
