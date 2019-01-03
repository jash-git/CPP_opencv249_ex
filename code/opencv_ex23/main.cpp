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
        imshow("Lena_original", src);

        Mat gray_src,dst;

        cvtColor(src, gray_src, CV_BGR2GRAY);
        imshow("Lena_gray", gray_src);

        /*
        使用時機:我們可透過拉伸直方圖，使直方圖覆蓋所有強度範圍，這種方法的確能提高影像對比度，但是在多數情況，影像模糊不是因為過窄的強度範圍，而是某區間的像素強度比例過高，這時可以製作一個映射表，使得調整之後的影像，能平均使用所有的強度，進而增加影像的整體對比度。

        OpenCV直方圖等化
        void equalizeHist(InputArray src, OutputArray dst)

        src：輸入圖，8位元單通道圖。
        dst：輸出圖，和輸入圖尺寸、型態相同。
        equalizeHist()函式可得到直方圖等化後的影像，以下為流程，OpenCV已將流程封裝好，使用時只要直接呼叫equalizeHist()函式即可：

        計算輸入圖的直方圖。
        將直方圖歸一到所有bin的總合為255。
        計算直方圖累計表。
        用直方圖累計表完成各強度的映射，所以假設強度30所累積的比例為20%，映射的強度即為255*0.2，由於我們直方圖歸一化到255，所以假設強度30所累積的值為20，映射的強度即為20。
        */
        equalizeHist(gray_src, dst);
        imshow("equalizeHist", dst);
    }

    waitKey(0);
    Pause();
    return 0;
}
