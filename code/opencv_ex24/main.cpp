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
        namedWindow("histogram", CV_WINDOW_AUTOSIZE);

        // 分通道显示
        vector<Mat> bgr_planes;
        /*
        split 函数
        用于将一幅多通道的图像的各个通道分离。
        这个函数的原型如下：

        void split(const Mat& src, vector<Mat_<_Tp> >& mv)
        */
        split(src, bgr_planes);

        // 计算直方图
        int histSize = 256;//灰階度0~255
        float range[] = { 0, 256 };
        const float *histRanges = { range };
        Mat b_hist, g_hist, r_hist;

        /*
        OpenCV計算直方圖
        OpenCV的calcHist()函式可得到一個影像的直方圖，為了使用上的彈性，參數有點複雜。

        void calcHist(const Mat* images, int nimages, const int* channels, InputArray mask, OutputArray hist, int dims, const int* histSize, const float** ranges, bool uniform=true, bool accumulate=false)

        images：輸入圖，可以一個或多個圖，深度必須為CV_8U或CV_32F，可為任意通道數，但是每張圖的尺寸和深度必須相同。
        nimages：有幾張輸入圖。
        channels：直方圖通道清單。
        mask：可有可無的遮罩。
        hist：輸出的直方圖
        dims：直方圖維度，必須為正數且不能超過CV_MAX_DIMS(目前為32)，假設為灰階圖的直方圖，每個像素只有強度資料，此時維度為1。
        histSize：直方圖橫軸(也稱bin)數目。
        ranges：直方圖的強度範圍，以8位元無負號的影像，就是[0,255]。
        uniform：各維度取值是否一致。
        accumulate：如果設定為true的話，在呼叫calcHist()這函式的時候，hist的內容不會被清掉，方便我們做多次的直方圖計算的累加。
        */
        calcHist(&bgr_planes[0], 1, 0, Mat(), b_hist, 1, &histSize, &histRanges, true, false);
        calcHist(&bgr_planes[1], 1, 0, Mat(), g_hist, 1, &histSize, &histRanges, true, false);
        calcHist(&bgr_planes[2], 1, 0, Mat(), r_hist, 1, &histSize, &histRanges, true, false);

        // 归一化
        int hist_h = 400;
        int hist_w = 512;
        int bin_w = hist_w / histSize;
        Mat histImage(hist_w, hist_h, CV_8UC3, Scalar(0, 0, 0));//建立空白畫布

        /*
        歸一化函式
        normalize(src, dst, alpha, beta, norm_type, dtype, mask)

        src-輸入陣列。

        dst-與SRC大小相同的輸出陣列。

        α-範數值在範圍歸一化的情況下歸一化到較低的範圍邊界。

        β-上限範圍在範圍歸一化的情況下；它不用於範數歸一化。

        正規化-規範化型別（見下面的細節）。
            NORM_MINMAX: 陣列的數值被平移或縮放到一個指定的範圍，線性歸一化。
            NORM_INF: 歸一化陣列的（切比雪夫距離）L∞範數(絕對值的最大值)
            NORM_L1:  歸一化陣列的（曼哈頓距離）L1-範數(絕對值的和)
            NORM_L2: 歸一化陣列的(歐幾里德距離)L2-範數

        dType——當輸出為負時，輸出陣列具有與SRC相同的型別；否則，它具有與SRC相同的通道數和深度＝CVH-MatthAsHead（DyType）。
        */
        //否則像素太多會爆掉
        normalize(b_hist, b_hist, 0, hist_h, NORM_MINMAX, -1, Mat());
        normalize(g_hist, g_hist, 0, hist_h, NORM_MINMAX, -1, Mat());
        normalize(r_hist, r_hist, 0, hist_h, NORM_MINMAX, -1, Mat());

        // render histogram chart
        /*
        功能：cvRound(), cvFloor(), cvCeil()函數講解。

        函數cvRound，cvFloor，cvCeil 都是用一種舍入的方法將輸入浮點數轉換成整數：

        cvRound()：返回跟參數最接近的整數值，即四捨五入；
        cvFloor()：返回不大於參數的最大整數值，即向下取整；
        cvCeil()：返回不小於參數的最小整數值，即向上取整；
        */
        for (int i = 1; i < histSize; i++) {
            line(histImage, Point((i - 1)*bin_w, hist_h - cvRound(b_hist.at<float>(i - 1))),
                Point((i)*bin_w, hist_h - cvRound(b_hist.at<float>(i))), Scalar(255, 0, 0), 2, CV_AA);

            line(histImage, Point((i - 1)*bin_w, hist_h - cvRound(g_hist.at<float>(i - 1))),
                Point((i)*bin_w, hist_h - cvRound(g_hist.at<float>(i))), Scalar(0, 255, 0), 2, CV_AA);

            line(histImage, Point((i - 1)*bin_w, hist_h - cvRound(r_hist.at<float>(i - 1))),
                Point((i)*bin_w, hist_h - cvRound(r_hist.at<float>(i))), Scalar(0, 0, 255), 2, CV_AA);
        }

        imshow("histogram", histImage);

    }

    waitKey(0);
    Pause();
    return 0;
}
