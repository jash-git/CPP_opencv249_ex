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
int main()
{
    Mat src00, dst00;
	Mat src01, dst01;
	src00 = imread("Lena_original.jpg");
	if (!src00.data) {
		printf("could not load image...\n");
	}
	else
    {
        namedWindow("Lena_original", CV_WINDOW_AUTOSIZE);
        imshow("Lena_original", src00);
        cvtColor(src00, src01, CV_BGR2GRAY);//imread("Lena_original.jpg",IMREAD_GRAYSCALE);
        namedWindow("cvtColor()~CV_BGR2GRAY", CV_WINDOW_AUTOSIZE);
        imshow("cvtColor()~CV_BGR2GRAY", src01);
        int cols = src00.cols;
        int rows = src00.rows;
        int channels00 = src00.channels();
        int channels01 = src01.channels();
        printf("rows : %d cols : %d\n", rows, cols);
        printf("channels00 : %d channels01 : %d\n", channels00, channels01);

        dst00=src00.clone();
        dst01=src01.clone();

        for(int i=0;i<cols;i++)
        {
            Vec3f ReadRGB = dst00.at<Vec3f>(0, i);
            float blue = ReadRGB.val[0];
            float green = ReadRGB.val[1];
            float red = ReadRGB.val[2];

            dst00.at<Vec3b>(0,i)[0]=red; // blue
            dst00.at<Vec3b>(0,i)[1]=green; // green
            dst00.at<Vec3b>(0,i)[2]=blue; // red

            uchar ReadGRAY = dst01.at<uchar>(0, i);
            dst01.at<uchar>(0, i)= 255;//(255-ReadGRAY);



        }
        namedWindow("Lena_test01", CV_WINDOW_AUTOSIZE);
        imshow("Lena_test01", dst00);
        namedWindow("Lena_test02", CV_WINDOW_AUTOSIZE);
        imshow("Lena_test02", dst01);
    }

	waitKey(0);
    Pause();
    return 0;
}
