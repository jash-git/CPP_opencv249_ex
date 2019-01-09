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

Mat src, dst;
const char* output_win = "findcontours-demo";
int threshold_value = 100;
int threshold_max = 255;
RNG rng;
void Demo_Contours(int, void*);
int main()
{
	Mat srcImg = imread("Patrick Star.jpg");
	if (!srcImg.data)
    {
		printf("could not load image...\n");
	}
    else
    {
        namedWindow("input-image", CV_WINDOW_AUTOSIZE);
        imshow("input-image",srcImg);
        namedWindow(output_win, CV_WINDOW_AUTOSIZE);
        cvtColor(srcImg, src, CV_BGR2GRAY);

        const char* trackbar_title = "Threshold Value:";
        createTrackbar(trackbar_title, output_win, &threshold_value, threshold_max, Demo_Contours);
        Demo_Contours(0, 0);
    }
    waitKey(0);
    Pause();
    return 0;
}
void Demo_Contours(int, void*) {
	Mat canny_output;
	vector< vector<Point> > contours;
	vector<Vec4i> hierachy;

    /*
    OpenCV canny
        void Canny(InputArray image, OutputArray edges, double threshold1, double threshold2, int apertureSize=3, bool L2gradient=false)

            src：輸入圖，單通道8位元圖。
            dst：輸出圖，尺寸、型態和輸入圖相同。
            threshold1：第一個閾值。
            threshold2：第二個閾值。
            apertureSize ：Sobel算子的核心大小。
            L2gradient ：梯度大小的算法，預設為false。
    */
	Canny(src, canny_output, threshold_value, threshold_value * 2, 3, false);
    /*
    OpenCV找輪廓
        void findContours(InputOutputArray image, OutputArrayOfArrays contours, int mode, int method, Point offset=Point())

            image：輸入圖，使用八位元單通道圖，所有非零的像素都會列入考慮，通常為二極化後的圖。
            contours：包含所有輪廓的容器(vector)，每個輪廓都是儲存點的容器(vector)，所以contours的資料結構為vector< vector>。
            hierarchy：可有可無的輸出向量，以階層的方式記錄所有輪廓。
            mode：取得輪廓的模式。
                CV_RETR_EXTERNAL：只取最外層的輪廓。
                CV_RETR_LIST：取得所有輪廓，不建立階層(hierarchy)。
                CV_RETR_CCOMP：取得所有輪廓，儲存成兩層的階層，首階層為物件外圍，第二階層為內部空心部分的輪廓，如果更內部有其餘物件，包含於首階層。
                CV_RETR_TREE：取得所有輪廓，以全階層的方式儲存。
            method：儲存輪廓點的方法，有以下幾種可選擇：
                CV_CHAIN_APPROX_NONE：儲存所有輪廓點。
                CV_CHAIN_APPROX_SIMPLE：對水平、垂直、對角線留下頭尾點，所以假如輪廓為一矩形，只儲存對角的四個頂點。
    */
	findContours(canny_output, contours, hierachy, RETR_TREE, CHAIN_APPROX_SIMPLE, Point(0, 0));

	dst = Mat::zeros(src.size(), CV_8UC3);//CV_8UC3	位元深度為8，無負號，通道數3 -> 0~255,BGR

	RNG rng(12345);
	for (size_t i = 0; i < contours.size(); i++) {

		Scalar color = Scalar(rng.uniform(0, 255), rng.uniform(0, 255), rng.uniform(0, 255));
    /*
    OpenCV畫輪廓線
        void drawContours(InputOutputArray image, InputArrayOfArrays contours, int contourIdx, const Scalar& color, int thickness=1, int lineType=8, InputArray hierarchy=noArray(), int maxLevel=INT_MAX, Point offset=Point())

            image：輸入輸出圖，會將輪廓畫在此影像上。
            contours：包含所有輪廓的容器(vector)，也就是findContours()所找到的contours。
            contourIdx：指定畫某個輪廓。
            color：繪製的顏色。
            lineType：繪製的線條型態。
            hierarchy：輪廓階層，也就是findContours()所找到的hierarchy。
            maxLevel：最大階層的輪廓，可以指定想要畫的輪廓，有輸入hierarchy時才會考慮，輸入的值代表繪製的層數。
    */
		drawContours(dst, contours, i, color, 1, 8, hierachy, 0, Point(0, 0));
	}

	imshow(output_win, dst);
}
