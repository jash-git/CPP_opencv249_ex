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
int threshold_value = 127;
int threshold_max = 255;
int type_value = 2;
int type_max = 4;
const char* output_title = "binary image";
void Threshold_Demo(int, void*);
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

        namedWindow(output_title, CV_WINDOW_AUTOSIZE);
        createTrackbar("Threshold Value:", output_title, &threshold_value, threshold_max, Threshold_Demo);
        createTrackbar("Type Value:", output_title, &type_value, type_max, Threshold_Demo);
        Threshold_Demo(0, 0);


    }
    waitKey(0);
    Pause();
    return 0;
}
void Threshold_Demo(int, void*) {
    Mat gray_src, dst00,dst01,dst02,dst03;
	cvtColor(src, gray_src, CV_BGR2GRAY);
	threshold(gray_src, dst00, threshold_value, 255, 16 | type_value);//THRESH_TRIANGLE=16 ~ https://blog.csdn.net/foryouslgme/article/details/51803039
	imshow(output_title, dst00);

    //Sobel_X
    Mat Sobel_X = (Mat_<int>(3, 3) << -1, 0, 1, -2,0,2,-1,0,1);
    filter2D(dst00, dst01, -1, Sobel_X, Point(-1, -1), 0.0);
    imshow("Sobel_X", dst01);

    //Sobel_Y
    Mat Sobel_Y = (Mat_<int>(3, 3) << -1, -2, -1, 0,0,0, 1,2,1);
    filter2D(dst00, dst02, -1, Sobel_Y, Point(-1, -1), 0.0);
    imshow("Sobel_Y", dst02);

    //Laplacian
    Mat Laplacian = (Mat_<int>(3, 3) << 0, -1, 0, -1, 4, -1, 0, -1, 0);
    filter2D(dst00, dst03, -1, Laplacian, Point(-1, -1), 0.0);
    imshow("Laplacian", dst03);
}
