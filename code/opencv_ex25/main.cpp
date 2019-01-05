#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/ml/ml.hpp>

#include <iostream>
#include <cstdio>
#include <string>

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
Mat src01;//input image
Mat src02;//input image
void Pause()
{
    printf("Press Enter key to continue...");
    fgetc(stdin);
}
int main()
{
    Mat input01,input02;

	input01 = imread("Lena01.jpg");
	input02 = imread("Lena02.png");
	if ((!input01.data)&&(!input02.data))
    {
		printf("could not load image...\n");
	}
    else
    {
        //放大
        pyrUp(input01, src01, Size(input01.cols*2, input01.rows*2));
        pyrUp(input02, src02, Size(input02.cols*2, input02.rows*2));

        namedWindow("Lena01", CV_WINDOW_AUTOSIZE);
        namedWindow("Lena02", CV_WINDOW_AUTOSIZE);


        Mat hsvbase, hsvtest;
        cvtColor(src01, hsvbase, CV_BGR2HSV);
        cvtColor(src02, hsvtest, CV_BGR2HSV);

        int h_bins = 50; int s_bins = 60;
        int histSize[] = { h_bins, s_bins };
        // hue varies from 0 to 179, saturation from 0 to 255
        float h_ranges[] = { 0, 180 };
        float s_ranges[] = { 0, 256 };
        const float* ranges[] = { h_ranges, s_ranges };
        // Use the o-th and 1-st channels
        int channels[] = { 0, 1 };
        //因為channels不是單一所以要使用MatND才支援多維
        MatND hist_base;
        MatND hist_test;

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
        calcHist(&hsvbase, 1,  channels, Mat(), hist_base, 2, histSize, ranges, true, false);
        normalize(hist_base, hist_base, 0, 1, NORM_MINMAX, -1, Mat());

        calcHist(&hsvtest, 1, channels, Mat(), hist_test, 2, histSize, ranges, true, false);

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
        normalize(hist_test, hist_test, 0, 1, NORM_MINMAX, -1, Mat());

        /*
        OpenCV直方圖比較
        double compareHist(InputArray H1, InputArray H2, int method)

        H1：第一個直方圖。
        H2：第二個直方圖，須和第一個直方圖尺寸相同。
        method：比較方法，有以下四種方法可選擇，不論選擇何種，皆會返回一個比較值：
            CV_COMP_CORREL：信號處理中的歸一化互相關方法，N為bin的總個數
            CV_COMP_CHISQR：歸一化的平方和
            CV_COMP_INTERSECT ：比較每個直方圖bin的值，總和較小的那個，也就是假如兩個直方圖沒有共同的值，計算結果為0，完全相同的直方圖，返回值等於像素的個數。
            CV_COMP_BHATTACHARYYA：統計學中用於評估兩個概率分布相似性
        */
        float basebase = compareHist(hist_base, hist_base, CV_COMP_CORREL);
        float basetest = compareHist(hist_base, hist_test, CV_COMP_CORREL);
        printf("basebase=%f\n", basebase);
        printf("basetest=%f\n", basetest);
        string strbasebase="basebase:",strbasetest="basetest:";
        char buffer[100] = {};
        sprintf(buffer, "%f", basebase);
        strbasebase += buffer;
        sprintf(buffer, "%f", basetest);
        strbasetest += buffer;

        /*
        OpenCV 畫文字字串
        void putText(Mat& img, const string& text, Point org, int fontFace, double fontScale, Scalar color, int thickness=1, int lineType=8, bool bottomLeftOrigin=false)

        img：輸入圖，字串會畫在上面。
        text：輸出字串，OpenCV目前沒有支援中文文字顯現。
        org：文字左下角位置。
        fontFace：字體樣式。
        fontScale：字體大小。
        color：字串顏色。
        thickness：構成字串的線寬度。
        lineType：通道型態，有以下三種可選： 8：8通道連結。 4：4通道連結。 CV_AA：消除鋸齒(antialiased line)，消除顯示器畫面橢圓邊緣的凹凸鋸齒。
        */
        putText(src01, strbasebase, Point(50, 50), CV_FONT_HERSHEY_COMPLEX, 1, Scalar(255, 0, 0), 2, CV_AA);
        putText(src02, strbasetest, Point(50, 50), CV_FONT_HERSHEY_COMPLEX, 1, Scalar(255, 0, 0), 2, CV_AA);

        imshow("Lena01", src01);
        imshow("Lena02", src02);
    }

    waitKey(0);
    Pause();
    return 0;
}
