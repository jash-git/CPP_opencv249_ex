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
    Mat input,gray_src,dst;
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

        Mat Scharr_x, Scharr_y;
        /*
        void Scharr(InputArray src, OutputArray dst, int ddepth, int dx, int dy, double scale=1, double delta=0, int borderType=BORDER_DEFAULT)

        或是Sobel(src, dst, ddepth, dx, dy, CV_SCHARR)，兩者效果相同。

        src：輸入圖。
        dst：輸出圖，和輸入圖有相同的尺寸和通道數。
        ddepth：輸出圖的深度，使用方式和Sobel相同。
        dx：x方向的微分階數。
        dy：y方向的微分階數。
        scale：縮放值
        delta：偏移量。
        */
        Scharr(gray_src, Scharr_x, CV_16S, 1, 0);
        Scharr(gray_src, Scharr_y, CV_16S, 0, 1);
        convertScaleAbs(Scharr_x, Scharr_x);
        convertScaleAbs(Scharr_y, Scharr_y);
        //--imshow("Scharr_x", Scharr_x);
        //--imshow("Scharr_y", Scharr_y);


        /*
        void Sobel(InputArray src, OutputArray dst, int ddepth, int dx, int dy, int ksize=3, double scale=1, double delta=0, int borderType=BORDER_DEFAULT)
        src：輸入圖。
        dst：輸出圖，和輸入圖有相同的尺寸和通道數。
        ddepth：輸出圖的深度，假設輸入圖為CV_8U, 支援CV_8U、CV_16S、CV_32F、CV_64F，假設輸入圖為 CV_16U, 支援CV_16U、CV_32F、CV_64F。
        dx：x方向的微分階數。
        dy：y方向的微分階數。
        ksize：核心，必須為1、3、5或7。
        scale：縮放值。
        delta：偏移量。
        */
        Mat Sobel_x, Sobel_y;
        Sobel(gray_src, Sobel_x, CV_16S, 1, 0, 3);
        Sobel(gray_src, Sobel_y, CV_16S, 0, 1, 3);
        /*
        計算輸入圖各像素，並將結果轉成8位元圖
        void convertScaleAbs(InputArray src, OutputArray dst, double alpha=1, double beta=0)
        src：輸入圖。
        dst：輸出圖。
        alpha：選擇性的乘法因子。
        beta：選擇性的加法因子。
        此函式主要進行3步驟；1.計算 2.取絕對值 3.轉成無正負號8位元圖
        */
        convertScaleAbs(Sobel_x, Sobel_x);
        convertScaleAbs(Sobel_y, Sobel_y);
        imshow("Sobel_x", Sobel_x);
        imshow("Sobel_y", Sobel_y);

        Mat Sobel_xy = Mat(Sobel_x.size(), Sobel_x.type());
        int width = Sobel_x.cols;
        int height = Sobel_y.rows;
        for (int row = 0; row < height; row++) {
            for (int col = 0; col < width; col++) {
                int xg = Sobel_x.at<uchar>(row, col);
                int yg = Sobel_y.at<uchar>(row, col);
                int xy = xg + yg;
                /*
                用saturate_cast將每次的計算結果限定在合理範圍，以本例來說就是從0到255，超過255會設定成255，小於0會設定成0。
                OpenCV 限定合理範圍：template< … > _Tp saturate_cast(_Tp2 v)
                v：輸入參數，會讓此值在合理範圍。
                saturate_cast使用模板，所以呼叫時要指定像素深度。
                */
                Sobel_xy.at<uchar>(row, col) = saturate_cast<uchar>(xy);
            }
        }
        imshow("Sobel_xy", Sobel_xy);

        Mat Sobel_x_y01 = Mat(Sobel_x.size(), Sobel_x.type());
        /*
        OpenCV影像相加：void addWeighted(InputArray src1, double alpha, InputArray src2, double beta, double gamma, OutputArray dst, int dtype=-1)
        src1：輸入圖。
        alpha：src1的權重。
        src2：輸入圖，和src1的尺寸和通道數相同。
        beta：src2的權重。
        gamma：兩圖相加後再增加的值。
        dst：輸出圖，輸出矩陣和輸入矩陣有相同的尺寸和通道數。
        dtype：可有可無的輸出圖深度。
        */
        addWeighted(Sobel_x, 0.5, Sobel_y, 0.5, 0, Sobel_x_y01);//Sobel_x*0.5+Sobel_y*0.5
        imshow("Sobel_x+y01", Sobel_x_y01);

        Mat Sobel_x_y02 = Mat(Sobel_x.size(), Sobel_x.type());//Sobel_x+Sobel_y
        /*
        OpenCV影像相加：void add(InputArray src1, InputArray src2, OutputArray dst, InputArray mask=noArray(), int dtype=-1)

        src1 ：輸入圖或強度值。
        src2 ：輸入圖或強度值。
        dst：輸出圖，輸出圖和輸入圖有相同的尺寸和通道數。
        mask：可有可無的遮罩，8位元單通道圖，指定那些像素要計算。
        dtype：可有可無的輸出圖深度。
        */
        add(Sobel_x, Sobel_y, Sobel_x_y02);
        imshow("Sobel_x+y02", Sobel_x_y02);
    }
    waitKey(0);
    Pause();
    return 0;
}
