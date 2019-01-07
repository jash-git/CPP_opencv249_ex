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

Mat input;
Mat temp;
Mat dst;
int match_method = TM_SQDIFF;
int max_track = 5;
void Match_Demo(int, void*);
int main()
{

	input = imread("input.png");
	if (!input.data)
    {
		printf("could not load image...\n");
	}
    else
    {
        namedWindow("input", CV_WINDOW_AUTOSIZE);
        namedWindow("temp", CV_WINDOW_AUTOSIZE);
        namedWindow("match_output", CV_WINDOW_NORMAL);
        imshow("input", input);
        temp = imread("temp.png");
        imshow("temp", temp);

        const char* trackbar_title = "Match Algo Type:";
        createTrackbar(trackbar_title, "match_output", &match_method, max_track, Match_Demo);
        Match_Demo(0, 0);
    }
    waitKey(0);
    Pause();
    return 0;
}
void Match_Demo(int, void*) {
	int width = input.cols - temp.cols + 1;
	int height = input.rows - temp.rows + 1;
	Mat result(width, height, CV_32FC1);

	/*
    影像模板比對
        void matchTemplate(InputArray image, InputArray templ, OutputArray result, int method)

        image：輸入圖，必須為 8位元或浮點數圖。
        templ：輸入的template，尺寸必須小於輸入圖，形態需相同。
        result：比較結果圖，必須為單通道32位元浮點數圖，如果image的尺寸為W x H，templ的尺寸為w x h，則result的尺寸為(W-w+1)x(H-h+1)。
        method：比較方法，有以下六種方法可選擇：
            method=CV_TM_SQDIFF
            method=CV_TM_SQDIFF_NORMED
            method=CV_TM_CCORR
            method=CV_TM_CCORR_NORMED
            method=CV_TM_CCOEFF
            method=CV_TM_CCOEFF_NORMED

        當我們的參數為CV_TM_SQDIFF時，計算結果較小時相似度較高，當我們參數為CV_TM_CCORR、CV_TM_CCOEF時，計算結果較大時相似度較高。
	*/
	matchTemplate(input, temp, result, match_method);

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
	normalize(result, result, 0, 1, NORM_MINMAX, -1, Mat());

	Point minLoc;
	Point maxLoc;
	double min, max;
	input.copyTo(dst);
	Point temLoc;
	/*
    當我們得到比較圖後，根據由比較方式，選擇比較圖最小或最大值的地方，就是目標影像的位置。
        void minMaxLoc(InputArray src, double* minVal, double* maxVal=0, Point* minLoc=0, Point* maxLoc=0, InputArray mask=noArray())

        src：輸入圖。
        minVal：極小值，可輸入NULL表示不需要。
        maxVal ：極大值，可輸入NULL表示不需要。
        minLoc：極小值的位置，可輸入NULL表示不需要。
        maxLoc：極大值的位置，可輸入NULL表示不需要。
        mask：可有可無的遮罩。
	*/
	minMaxLoc(result, &min, &max, &minLoc, &maxLoc, Mat());

	if (match_method == TM_SQDIFF || match_method == TM_SQDIFF_NORMED) {
		temLoc = minLoc;
	} else {
		temLoc = maxLoc;
	}

	rectangle(dst, Rect(temLoc.x, temLoc.y, temp.cols, temp.rows), Scalar(0, 0, 255), 2, 8);

	//rectangle(result, Rect(temLoc.x, temLoc.y, temp.cols, temp.rows), Scalar(0, 0, 255), 2, 8);
	//imshow("temp", result);

	imshow("match_output", dst);
}
