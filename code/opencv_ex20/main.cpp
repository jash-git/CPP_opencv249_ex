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
	input = imread("hough01.png");
	if (!input.data)
    {
		printf("could not load image...\n");
	}
    else
    {
        //縮小
        pyrDown(input, src, Size(input.cols/2, input.rows/2));



        char INPUT_TITLE[] = "input image";
        char OUTPUT_TITLE[] = "hough-line-detection";
        namedWindow(INPUT_TITLE, CV_WINDOW_AUTOSIZE);
        namedWindow(OUTPUT_TITLE, CV_WINDOW_AUTOSIZE);
        imshow(INPUT_TITLE, src);

        Mat src_gray,dst;
        Canny(src, src_gray, 150, 200);
        cvtColor(src_gray, dst, CV_GRAY2BGR);
        imshow("edge image", src_gray);

        /*
        OpenCV 直線偵測
        void HoughLines(InputArray image, OutputArray lines, double rho, double theta, int threshold, double srn=0, double stn=0)

        image：輸入圖，8位元單通道二值化圖。
        lines：將所有線的資料存在vector< Vec2f >，Vec2f為每個線的資料，分別有ρ、θ這兩個參數，ρ表示和左上角(0,0)的距離，θ是線的旋轉角度，單位弧度，垂直線的θ為0，水平線的θ為π/2。
        rho：距離解析度，越小表示定位要求越準確，但也較易造成應該是同條線的點判為不同線。 1
        theta：角度解析度，越小表示角度要求越準確，但也較易造成應該是同條線的點判為不同線。 CV_PI / 180
        threshold：累積個數閾值，超過此值的線才會存在lines這個容器內。 10
        srn：可有可無的距離除數。
        stn：可有可無的角度除數。
        */

        /*
        vector<Vec2f> lines;
        HoughLines(src_gray, lines, 1, CV_PI / 180, 140, 0, 0);

        Scalar color = Scalar(0, 0, 255);
        for (size_t i = 0; i < lines.size(); i++)
        {
            float rho = lines[i][0]; // 极坐标中的r长度
            float theta = lines[i][1]; // 极坐标中的角度
            Point pt1, pt2;
            double a = cos(theta), b = sin(theta);
            double x0 = a*rho, y0 = b*rho;
            // 转换为平面坐标的四个点
            pt1.x = cvRound(x0 + 1000 * (-b));
            pt1.y = cvRound(y0 + 1000 * (a));
            pt2.x = cvRound(x0 - 1000 * (-b));
            pt2.y = cvRound(y0 - 1000 * (a));
            line(dst, pt1, pt2, color, 1, CV_AA);
        }
        //*/

        /*
        OpenCV 直線偵測
        void HoughLinesP(InputArray image, OutputArray lines, double rho, double theta, int threshold, double minLineLength=0, double maxLineGap=0)

        image：輸入圖，8位元單通道二值化圖。
        lines：將所有線的資料存在vector< Vec4i >，Vec4i為每個線段的資料，分別有x1、y1、x2、y2這四個值，(x1，y1)和(x2，y2)分別表示線段的頭尾頂點。
        rho：距離解析度，越小表示定位要求越準確，但也較易造成應該是同條線的點判為不同線。 1
        theta：角度解析度，越小表示角度要求越準確，但也較易造成應該是同條線的點判為不同線。 CV_PI/180
        threshold：累積個數閾值，超過此值的線才會存在lines這個容器內。 10
        minLineLength ：線段最短距離，超過此值的線才會存在lines這個容器內。 0
        maxLineGap：最大間隔。 10
        )
        */
        //*
        vector<Vec4i> lines;
        HoughLinesP(src_gray, lines, 1, CV_PI/180, 10,0,10);
        for( size_t i = 0; i < lines.size(); i++ )
        {
            Vec4i l = lines[i];//Vec4i 就是Vec<int, 4>，里面存放４个int
            line( dst, Point(l[0], l[1]), Point(l[2], l[3]), Scalar(0,0,255), 1, CV_AA);
            //要划的线所在的图像：dst，　起点：Point(l[0], l[1])，　终点：Point(l[2], l[3])，　3 線寬 ， 颜色：Scalar(0,0,255)
        }
        //*/

        imshow(OUTPUT_TITLE, dst);

    }
    waitKey(0);
    Pause();
    return 0;
}

