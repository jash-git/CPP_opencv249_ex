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
        Mat medianBlur;
        Mat bilateralFilter;

        namedWindow("Lena_original", CV_WINDOW_AUTOSIZE);
        imshow("Lena_original", src);

        char output_title00[] = "medianBlur";
        namedWindow(output_title00, CV_WINDOW_AUTOSIZE);
        cv::medianBlur(src, medianBlur, 3);
        imshow(output_title00, medianBlur);

        char output_title01[] = "bilateralFilter";
        cv::bilateralFilter(src, bilateralFilter, 15, 100, 5);
        //- 15 –計算的半徑，半徑之內的像數都會被納入計算，如果提供-1 則根據sigma space參數取值
        //- 150 – sigma color 決定多少差值之內的像素會被計算
        //- 3 – sigma space 如果d的值大於0則聲明無效，否則根據它來計算d值
        namedWindow(output_title01, CV_WINDOW_AUTOSIZE);
        imshow(output_title01, bilateralFilter);

        Mat resultImg00;
        Mat resultImg01;
        Mat kernel = (Mat_<int>(3, 3) << 0, -1, 0, -1, 5, -1, 0, -1, 0);

        filter2D(medianBlur, resultImg00, -1, kernel, Point(-1, -1), 0);
        namedWindow("medianBlur-Final Result", CV_WINDOW_AUTOSIZE);
        imshow("medianBlur-Final Result", resultImg00);


        filter2D(bilateralFilter, resultImg01, -1, kernel, Point(-1, -1), 0);
        namedWindow("bilateralFilter-Final Result", CV_WINDOW_AUTOSIZE);
        imshow("bilateralFilter-Final Result", resultImg01);
    }
    waitKey(0);
    return 0;
}
