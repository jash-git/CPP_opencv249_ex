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
        dst00=Mat::zeros(src00.size(),src00.type());//src00.clone();
        dst01=Mat::zeros(src01.size(),src01.type());//src01.clone();
        int cols = src00.cols;
        int rows = src00.rows;
        int channels00 = src00.channels();
        int channels01 = src01.channels();
        printf("rows : %d cols : %d\n", rows, cols);
        printf("channels00 : %d channels01 : %d\n", channels00, channels01);

        float alpha=1.5;
        float beta=0.5;

        //Mat m1;
        //src00.convertTo(m1,CV_32F);

        for(int x=0;x<cols;x++)
        {
            for(int y=0;y<rows;y++)
            {
                //調整圖像亮度和對比度屬於像素變換-點操作
                //output(x,y)=A*input(x,y)+B

                dst01.at<uchar>(y, x)= saturate_cast<uchar>(alpha*src01.at<uchar>(y, x)+beta);//確保值大小範圍為0~255之間

                Vec3b ReadRGB = src00.at<Vec3b>(y, x);//Vec3f ReadRGB = m1.at<Vec3f>(y, x);
                int b=ReadRGB.val[0];
                int g=ReadRGB.val[1];
                int r=ReadRGB.val[2];
                dst00.at<Vec3b>(y,x)[0]=saturate_cast<uchar>(alpha*b+beta);
                dst00.at<Vec3b>(y,x)[1]=saturate_cast<uchar>(alpha*g+beta);
                dst00.at<Vec3b>(y,x)[2]=saturate_cast<uchar>(alpha*r+beta);
            }
        }
        namedWindow("Lena_colr_line transform", CV_WINDOW_AUTOSIZE);
        imshow("Lena_colr_line transform", dst00);
        namedWindow("Lena_gray_line transform", CV_WINDOW_AUTOSIZE);
        imshow("Lena_gray_line transform", dst01);
    }

    waitKey(0);
    Pause();
    return 0;
}
