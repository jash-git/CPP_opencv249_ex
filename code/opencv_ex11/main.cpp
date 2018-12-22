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
Mat src1;//threshold
Mat dst01,dst02,dst03,dst04,dst05;

char OUTPUT_WIN01[] = "Lena_BINARY";
char OUTPUT_WIN02[] = "CV_MOP_OPEN";
char OUTPUT_WIN03[] = "CV_MOP_CLOSE";
char OUTPUT_WIN04[] = "CV_MOP_GRADIENT";
char OUTPUT_WIN05[] = "CV_MOP_TOPHAT";
char OUTPUT_WIN06[] = "CV_MOP_BLACKHAT";
int element_size = 120;
int max_size = 255;
void CallBack_Threshold(int, void*);

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
        namedWindow("Lena_original", CV_WINDOW_AUTOSIZE);
        imshow("Lena_original", src);

        namedWindow(OUTPUT_WIN01, CV_WINDOW_AUTOSIZE);
        createTrackbar("Element Size :", OUTPUT_WIN01, &element_size, max_size, CallBack_Threshold);
        CallBack_Threshold(0, 0);


    }
    waitKey(0);
    return 0;
}
void CallBack_Threshold(int, void*) {
	int s = element_size;
    threshold(src,src1,s,255,THRESH_BINARY);//設定門閥值灰階轉二值化 < s->0, > s->255

	imshow(OUTPUT_WIN01, src1);
	Mat kernel = getStructuringElement(MORPH_RECT, Size(11, 11), Point(-1, -1));//Size內數字越大，運算遮罩越大(腐蝕或膨脹越明顯)

	namedWindow(OUTPUT_WIN02, CV_WINDOW_AUTOSIZE);
	morphologyEx(src1, dst01, CV_MOP_OPEN, kernel);
	imshow(OUTPUT_WIN02, dst01);

	namedWindow(OUTPUT_WIN03, CV_WINDOW_AUTOSIZE);
	morphologyEx(src1, dst02, CV_MOP_CLOSE, kernel);
	imshow(OUTPUT_WIN03, dst02);

	namedWindow(OUTPUT_WIN04, CV_WINDOW_AUTOSIZE);
	morphologyEx(src1, dst03, CV_MOP_GRADIENT, kernel);
	imshow(OUTPUT_WIN04, dst03);

	namedWindow(OUTPUT_WIN05, CV_WINDOW_AUTOSIZE);
	morphologyEx(src1, dst04, CV_MOP_TOPHAT, kernel);
	imshow(OUTPUT_WIN05, dst04);

	namedWindow(OUTPUT_WIN06, CV_WINDOW_AUTOSIZE);
	morphologyEx(src1, dst05, CV_MOP_BLACKHAT, kernel);
	imshow(OUTPUT_WIN06, dst05);

	return;
}
