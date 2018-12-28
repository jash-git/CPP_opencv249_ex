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
Mat src,gray_src;//input image
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
    Mat input,dst;
	input = imread("Lena_original.jpg");
	if (!input.data)
    {
		printf("could not load image...\n");
	}
    else
    {
        //放大
        pyrUp(input, src, Size(input.cols*2, input.rows*2));
        GaussianBlur(src, dst, Size(3, 3), 0, 0);//高斯模糊GaussianBlur目的為了給圖像預處理時候減低噪聲(雜訊)
        cvtColor(dst, gray_src, CV_BGR2GRAY);//彩色轉灰階
        imshow("Lena_gray", gray_src);

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
    Mat dst00,dst01,dst02,dst03;
	threshold(gray_src, dst00, threshold_value, 255, 16 | type_value);//THRESH_TRIANGLE=16 ~ https://blog.csdn.net/foryouslgme/article/details/51803039
	imshow(output_title, dst00);

    //Sobel_X
    Mat Sobel_X = (Mat_<int>(3, 3) << -1, 0, 1, -2,0,2,-1,0,1);
    filter2D(dst00, dst01, -1, Sobel_X, Point(-1, -1), 0.0);
    imshow("Sobel_X(mask)", dst01);

    //Sobel_Y
    Mat Sobel_Y = (Mat_<int>(3, 3) << -1, -2, -1, 0,0,0, 1,2,1);
    filter2D(dst00, dst02, -1, Sobel_Y, Point(-1, -1), 0.0);
    imshow("Sobel_Y(mask)", dst02);

    dst03=Mat(dst01.size(), dst02.type());
    add(dst01, dst02, dst03);
    imshow("Sobel_XY(mask)", dst03);

}
