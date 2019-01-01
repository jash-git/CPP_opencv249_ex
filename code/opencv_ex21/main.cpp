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
	input = imread("hough02.png");
	if (!input.data)
    {
		printf("could not load image...\n");
	}
    else
    {
        src=input.clone();

        char INPUT_TITLE[] = "input image";
        char OUTPUT_TITLE[] = "hough circle demo";
        namedWindow(INPUT_TITLE, CV_WINDOW_AUTOSIZE);
        namedWindow(OUTPUT_TITLE, CV_WINDOW_AUTOSIZE);
        imshow(INPUT_TITLE, src);

        Mat src_gray,dst;
        Canny(src, src_gray, 150, 200);
        imshow("edge image", src_gray);

        /*
        OpenCV 偵測圓
        void HoughCircles(InputArray image, OutputArray circles, int method, double dp, double minDist, double param1=100, doubleparam2=100, int minRadius=0, int maxRadius=0)

        image：輸入圖，8位元單通道圖。
        circles：以vector< Vec3f >記錄所有圓的資訊，每個Vec3f紀錄一個圓的資訊，包含3個浮點數資料，分別表示x、y、radius。
        method：偵測圓的方法，目前只能使用CV_HOUGH_GRADIENT。
        dp：偵測解析度倒數比例，假設dp=1，偵測圖和輸入圖尺寸相同，假設dp=2，偵測圖長和寬皆為輸入圖的一半。
        minDist：圓彼此間的最短距離，太小的話可能會把鄰近的幾個圓視為一個，太大的話可能會錯過某些圓。
        param1：圓偵測內部會呼叫Canny()尋找邊界，param1就是Canny()的高閾值，低閾值自動設為此值的一半。
        param2：計數閾值，超過此值的圓才會存入circles。-調整重要參數
        minRadius：最小的圓半徑。
        maxRadius：最大的圓半徑。
        */

        vector<Vec3f> pcircles;
        HoughCircles(src_gray, pcircles, CV_HOUGH_GRADIENT, 1, 3, 100, 23, 5, 50);

        src.copyTo(dst);
        for (size_t i = 0; i < pcircles.size(); i++) {
            Vec3f cc = pcircles[i];
            circle(dst, Point(cc[0], cc[1]), cc[2], Scalar(0, 0, 255), 2, CV_AA);//圓周
            circle(dst, Point(cc[0], cc[1]), 2, Scalar(198, 23, 155), 2, CV_AA);//圓心
        }
        imshow(OUTPUT_TITLE, dst);

    }

    waitKey(0);
    Pause();
    return 0;
}
