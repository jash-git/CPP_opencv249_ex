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
Mat src00;//input image
Mat src01;//GRAY
Mat src02;//BIN
Mat dst01,dst02,dst03,dst04,dst05;

void Pause()
{
    printf("Press Enter key to continue...");
    fgetc(stdin);
}
int main()
{
	src00 = imread("input.png");
	if (!src00.data)
    {
		printf("could not load image...\n");
	}
    else
    {
        namedWindow("color_input", CV_WINDOW_AUTOSIZE);
        imshow("color_input", src00);

        cvtColor(src00, src01, CV_BGR2GRAY);
        namedWindow("gray_input", CV_WINDOW_AUTOSIZE);
        imshow("gray_input", src01);

        adaptiveThreshold(~src01, src02, 255, ADAPTIVE_THRESH_MEAN_C, THRESH_BINARY, 11, -2);
        //區域門閥值
        //src：輸入圖，只能輸入8位元單通道圖。
        //dst：輸出圖，尺寸大小、深度會和輸入圖相同。
        //maxValue：最大值，adaptiveThreshold會將像素分成0和maxValue。
        //adaptiveMethod：區域閾值方法：可以選擇ADAPTIVE_THRESH_MEAN_C或ADAPTIVE_THRESH_GAUSSIAN_C，兩者決定閾值的方式不同。
        //thresholdType：二值化型態：有THRESH_BINARY和THRESH_BINARY_INV兩種型態可選。
        //blockSize：區域尺寸，用幾個像素來決定閾值，只能選擇奇數像3、5、7……等。 PS 線條越粗則數值要越大
        //C：常數，計算閾值時，要從平均或加權平均減去的數。
        namedWindow("binary_input", CV_WINDOW_AUTOSIZE);
        imshow("binary_input", src02);

        //膨脹-輸出的像素值是結構元素覆蓋下輸入圖像的最大像素值
        //腐蝕-輸出的像素值是結構元素覆蓋下輸入圖像的最小像素值

        // 水平結構元素
        Mat hline = getStructuringElement(MORPH_RECT, Size(src00.cols/10, 1), Point(-1, -1));
        // 垂直結構元素
        Mat vline = getStructuringElement(MORPH_RECT, Size(1, src00.rows/5), Point(-1, -1));

        morphologyEx(src02, dst01, CV_MOP_OPEN, vline);//利用開運算保留垂直
        namedWindow("binary_input_OPEN_vline", CV_WINDOW_AUTOSIZE);
        imshow("binary_input_OPEN_vline", dst01);

        morphologyEx(src02, dst02, CV_MOP_OPEN, hline);//利用開運算保留水平
        namedWindow("binary_input_OPEN_hline", CV_WINDOW_AUTOSIZE);
        imshow("binary_input_OPEN_hline", dst02);

        //---------------------//

        // 矩形結構-去除干擾線留下文字
        dst03 = imread("chars.png",IMREAD_GRAYSCALE);
        adaptiveThreshold(~dst03, dst04, 255, ADAPTIVE_THRESH_MEAN_C, THRESH_BINARY, 11, -2);
        Mat kernel = getStructuringElement(MORPH_RECT, Size(3, 3), Point(-1, -1));
        Mat temp;
        erode(dst04, temp, kernel);//腐蝕
        dilate(temp, dst05, kernel);//膨脹
        //CV_MOP_OPEN:先腐蝕後膨脹-可以去掉小的對象，假設對像是前景色，背景是黑色
        namedWindow("binary_chars_OPEN", CV_WINDOW_AUTOSIZE);
        imshow("binary_chars_OPEN", dst05);

    }
    waitKey(0);
    return 0;
}
