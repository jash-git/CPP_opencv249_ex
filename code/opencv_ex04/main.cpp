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
    Mat src00, dst00,dst000;
	Mat src01, dst01;
	src00 = imread("image-20150507-1245-fctkfq.jpg");//imread("Lena_original.jpg");

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

        dst000.create(src00.size(),src00.type());

        for(int x=0;x<cols;x++)
        {
            for(int y=0;y<rows;y++)
            {

                dst01.at<uchar>(y, x)= 255-dst01.at<uchar>(y, x);

                Vec3b ReadRGB = dst00.at<Vec3b>(y, x);
                int b=ReadRGB.val[0];
                int g=ReadRGB.val[1];
                int r=ReadRGB.val[2];
                dst00.at<Vec3b>(y,x)[0]=255-b;
                dst00.at<Vec3b>(y,x)[1]=255-g;
                dst00.at<Vec3b>(y,x)[2]=255-r;

                dst000.at<Vec3b>(y,x)[0]=0;
                dst000.at<Vec3b>(y,x)[2]=g;
                dst000.at<Vec3b>(y,x)[3]=r;
            }
        }
        namedWindow("Lena_test01", CV_WINDOW_AUTOSIZE);
        imshow("Lena_test01", dst00);
        namedWindow("Lena_test02", CV_WINDOW_AUTOSIZE);
        imshow("Lena_test02", dst01);

        namedWindow("Lena_test03", CV_WINDOW_AUTOSIZE);
        imshow("Lena_test03", dst000);

    }

	waitKey(0);
    Pause();
    return 0;
}
