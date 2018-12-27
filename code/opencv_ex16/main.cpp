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
    Mat input,dst01,dst02,dst03,dst04;
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

        int top = (int)(0.2*src.rows);
        int bottom = (int)(0.2*src.rows);
        int left = (int)(0.2*src.cols);
        int right = (int)(0.2*src.cols);
        int borderType = BORDER_CONSTANT;//外推的值為常數，常在仿射變換、透視變換中使用。
        RNG rng(54321);
        Scalar color01 = Scalar(rng.uniform(0, 255), rng.uniform(0, 255), rng.uniform(0, 255));
        copyMakeBorder(src, dst01, top, bottom, left, right, borderType, color01);
        imshow("Border CONSTANT", dst01);

        borderType = BORDER_DEFAULT;
        Scalar color02 = Scalar(rng.uniform(0, 255), rng.uniform(0, 255), rng.uniform(0, 255));
        copyMakeBorder(src, dst02, top, bottom, left, right, borderType, color02);
        imshow("Border DEFAULT", dst02);

        borderType = BORDER_REPLICATE;//外推的值和邊緣值相同
        Scalar color03 = Scalar(rng.uniform(0, 255), rng.uniform(0, 255), rng.uniform(0, 255));
        copyMakeBorder(src, dst03, top, bottom, left, right, borderType, color03);
        imshow("Border REPLICATE", dst03);

        borderType = BORDER_REFLECT_101;//外推像素和影像邊界成鏡像映射
        Scalar color04 = Scalar(rng.uniform(0, 255), rng.uniform(0, 255), rng.uniform(0, 255));
        copyMakeBorder(src, dst04, top, bottom, left, right, borderType, color04);
        imshow("Border BORDER_REFLECT_101", dst04);


    }
    waitKey(0);
    Pause();
    return 0;
}
