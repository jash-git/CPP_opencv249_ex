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

Mat hsv; Mat hue;
int bins = 12;
void Hist_And_Backprojection(int, void*);
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

        const char*  window_image = "input image";
        namedWindow(window_image, CV_WINDOW_NORMAL);
        namedWindow("BackProj", CV_WINDOW_NORMAL);
        namedWindow("Histogram", CV_WINDOW_NORMAL);

        cvtColor(src, hsv, CV_BGR2HSV);
        hue.create(hsv.size(), hsv.depth());

        int nchannels[] = { 0, 0 };

        /*
        OpenCV之mixChannels()函数使用说明
        C++:   void  mixChannels (const Mat*  src , int  nsrc , Mat*  dst , int  ndst , const int*  fromTo , size_t  npairs );

        　　　　　　src– Input array or vector of matrices. All the matrices must have the same size and the same depth.

        　　　　　　　　　　输入矩阵，可以为一个也可以为多个，但是矩阵必须有相同的大小和深度.

        　　　　　　nsrcs– Number of matrices in src.

        　　　　　　　　　　输入矩阵的个数。

        　　　　　　dst– Output array or vector of matrices. All the matrices must be allocated. Their size and depth must be the same as in src[0].

        　　　　　　　　　　输出矩阵，可以为一个也可以为多个，但是所有的矩阵必须事先分配空间（如用create），大小和深度须与输入矩阵等同.

        　　　　　　ndsts– Number of matrices in dst.

        　　　　　　　　　　输出矩阵的个数。

        　　　　　　fromTo – Array of index pairs specifying which channels are copied and where. fromTo[k*2] is a 0-based index of the input channel in src.

        　　　　　　　　　　　fromTo[k*2+1] is an index of the output channel in dst. The continuous channel numbering is used: the first input image channels

        　　　　　　　　　　　are indexed from 0 to src[0].channels()-1 , the second input image channels are indexed from src[0].channels() to src[0].

        　　　　　　　　　　　channels() + src[1].channels()-1, and so on. The same scheme is used for the output image channels. As a special case,

        　　　　　　　　　　　when fromTo[k*2] is negative, the corresponding output channel is filled with zero .

        　　　　　　　　　　设置输入矩阵的通道对应输出矩阵的通道，规则如下：首先用数字标记输入矩阵的各个通道。输入矩阵个数可能多于一个并且每个矩阵的通道可能不一样，

        　　　　　　　　　　第一个输入矩阵的通道标记范围为：0 ~ src[0].channels()-1，第二个输入矩阵的通道标记范围为：src[0].channels() ~ src[0].channels()+src[1].channels()-1,

        　　　　　　　　　　以此类推；其次输出矩阵也用同样的规则标记，第一个输出矩阵的通道标记范围为：0 ~ dst[0].channels()-1，第二个输入矩阵的通道标记范围为：dst[0].channels()

        　　　　　　　　　　~ dst[0].channels()+dst[1].channels()-1,以此类推；最后，数组fromTo的第一个元素即fromTo[0]应该填入输入矩阵的某个通道标记，而fromTo的第二个元素即

        　　　　　　　　　　fromTo[1]应该填入输出矩阵的某个通道标记，这样函数就会把输入矩阵的fromTo[0]通道里面的数据复制给输出矩阵的fromTo[1]通道。fromTo后面的元素也是这个

        　　　　　　　　　　道理，总之就是一个输入矩阵的通道标记后面必须跟着个输出矩阵的通道标记。

        　　　　　　npairs– Number of index pairs in fromTo.

        　　　　　　　　　　即参数fromTo中的有几组输入输出通道关系，其实就是参数fromTo的数组元素个数除以2.
        */
        mixChannels(&hsv, 1, &hue, 1, nchannels, 1);

        createTrackbar("Histogram Bins:", window_image, &bins, 180, Hist_And_Backprojection);
        Hist_And_Backprojection(0, 0);

	imshow(window_image, src);
    }
    waitKey(0);
    Pause();
    return 0;
}

void Hist_And_Backprojection(int, void*) {
	float range[] = { 0, 180 };
	const float *histRanges = { range };
	Mat h_hist;
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
	calcHist(&hue, 1, 0, Mat(), h_hist, 1, &bins, &histRanges, true, false);

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
	normalize(h_hist, h_hist, 0, 255, NORM_MINMAX, -1, Mat());

	Mat backPrjImage;
    /*
    直方圖反投影(calcBackProject)
    直方圖本質上是一個統計圖，統計這個影像的強度分配情形，從這可以得到每個強度所佔全體的比例，也就是每個強度的發生機率。這也是直方圖反投影的概念，在影像檢索時，我們由已知ROI的直方圖，比較原始影像每個像素，看相對位置的強度屬於這個直方圖的機率有多少。

    void calcBackProject(const Mat* images, int nimages, const int* channels, InputArray hist, OutputArray backProject, const float**ranges, double scale=1, bool uniform=true)

    images：輸入圖，可以一個或多個圖，深度必須為CV_8U或CV_32F，可為任意通道數，但是每張圖的尺寸和深度必須相同。
    nimages：有幾張輸入圖。
    channels：直方圖通道清單。
    hist： 輸入比較的直方圖。
    backProject：輸出的反投影結果圖，單通道且尺寸、深度都和images[0]相同。
    ranges：直方圖的範圍，以8位元無負號的影像，就是[0,255]。
    scale：縮放因子。
    uniform：各維度取值是否一致。
    關於calcBackProject()這個函式，輸出的反投影結果圖backProject是一幅影像，每個像素代表原本強度在直方圖的機率值，所以假如輸入的直方圖hist是歸一化的，生成的值會在0.0到1.0之間，我們可以將縮放因子scale設成255.0，如此一來可以當作一般的8位元圖秀出結果，愈大的值代表屬於這個直方圖的機會越高。

    實際上做影像搜尋時，通常會考慮顏色訊息，畢竟單純強度的話資訊量不足，很難得到理想的結果，且直方圖反透影的結果，是得到影像各位置屬於此直方圖的概率，所以通常會搭配其他演算法使用。
    */
	calcBackProject(&hue, 1, 0, h_hist, backPrjImage, &histRanges, 1, true);
	imshow("BackProj", backPrjImage);

	int hist_h = 400;
	int hist_w = 400;
	Mat histImage(hist_w, hist_h, CV_8UC3, Scalar(0, 0, 0));
	int bin_w = (hist_w / bins);
	for (int i = 1; i < bins; i++) {
        /*
        OpenCV 畫矩形
        void rectangle(Mat& img, Point pt1, Point pt2, const Scalar& color, int thickness=1, int lineType=8, int shift=0)

        img：輸入圖，矩形會畫在上面。
        pt1：矩形頂點。
        pt2：矩形頂點，pt1的對角邊
        color：矩形的顏色。
        thickness：矩形的邊線寬度，輸入負值或CV_FILLED代表填滿矩形。
        lineType：通道型態，可輸入8、4、CV_AA： 8->8通道連結。 4->4通道連結。 CV_AA->消除鋸齒(antialiased line)，消除顯示器畫面線邊緣的凹凸鋸齒。
        */
		rectangle(histImage,
			Point((i - 1)*bin_w, (hist_h - cvRound(h_hist.at<float>(i - 1) * (400 / 255)))),
			//Point(i*bin_w, (hist_h - cvRound(h_hist.at<float>(i) * (400 / 255)))),
			Point(i*bin_w, hist_h),
			Scalar(0, 0, 255), -1);
	}
	imshow("Histogram", histImage);

	return;
}
