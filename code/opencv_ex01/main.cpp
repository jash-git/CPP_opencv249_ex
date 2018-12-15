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
	// read image
	Mat image = imread("Lena_original.jpg");

	// 对图像进行所有像素用 （255- 像素值）
	Mat invertImage;
	image.copyTo(invertImage);

	// 获取图像宽、高
	int channels = image.channels();
	int rows = image.rows;
	int cols = image.cols * channels;
	if (image.isContinuous()) {
		cols *= rows;
		rows = 1;
	}

	// 每个像素点的每个通道255取反
	uchar* p1;
	uchar* p2;
	for (int row = 0; row < rows; row++) {
		p1 = image.ptr<uchar>(row);// 获取像素指针
		p2 = invertImage.ptr<uchar>(row);
		for (int col = 0; col < cols; col++) {
			*p2 = 255 - *p1; // 取反
			p2++;
			p1++;
		}
	}

	// create windows
	namedWindow("My Test", CV_WINDOW_AUTOSIZE);
	namedWindow("My Invert Image", CV_WINDOW_AUTOSIZE);

	// display image
	imshow("My Test", image);
	imshow("My Invert Image", invertImage);


	waitKey(0);
	destroyWindow("My Test");
	destroyWindow("My Invert Image");
    Pause();
    return 0;
}
