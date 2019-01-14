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
	char input_win[] = "input image";
	char watershed_win[] = "watershed segmentation demo";
	Mat src = imread("03.png");
	if (!src.data)
    {
		printf("could not load image...\n");
	}
    else
    {
        namedWindow(input_win, CV_WINDOW_AUTOSIZE);
        imshow(input_win, src);

        //---
        //把背景從白色轉黑色
        for (int row = 0; row < src.rows; row++)
        {
            for (int col = 0; col < src.cols; col++)
            {
                if (src.at<Vec3b>(row, col) == Vec3b(255, 255, 255))
                {
                    src.at<Vec3b>(row, col)[0] = 0;
                    src.at<Vec3b>(row, col)[1] = 0;
                    src.at<Vec3b>(row, col)[2] = 0;
                }
            }
        }
        namedWindow("black background", CV_WINDOW_AUTOSIZE);
        imshow("black background", src);
        //---把背景從白色轉黑色

        //---
        //銳化濾波器(Sharpening filter)
        Mat kernel = (Mat_<float>(3, 3) << 1, 1, 1, 1, -8, 1, 1, 1, 1);// Laplacian二階微分運算3x3的遮罩
        Mat imgLaplance;
        Mat sharpenImg = src;
        //imshow("src -> sharpenImg01", sharpenImg);
        /*
        filter2D( InputArray src, OutputArray dst, int ddepth,
                  InputArray kernel, Point anchor=Point(-1,-1),
                  double delta=0, int borderType=BORDER_DEFAULT );
        */
        /*
        CV_8U	位元深度為8，無負號，通道數1
        CV_8S	位元深度為8，有負號，通道數1
        CV_16U	位元深度為16，無負號，通道數1
        CV_32F	浮點數資料，通道數1
        CV_8UC3	位元深度為8，無負號，通道數3
        */
        filter2D(src, imgLaplance, CV_32F, kernel, Point(-1, -1), 0, BORDER_DEFAULT);
        imshow("Laplance-CV32F", imgLaplance);

        src.convertTo(sharpenImg, CV_32F);
        //imshow("src -> sharpenImg_CV_32F", sharpenImg);

        Mat resultImg = sharpenImg - imgLaplance;

        resultImg.convertTo(resultImg, CV_8UC3);

        imgLaplance.convertTo(imgLaplance, CV_8UC3);
        imshow("Laplance-CV_8UC3", imgLaplance);
        imshow("sharpen image", resultImg);
        //---銳化濾波器(Sharpening filter)

        //---
        //彩色轉灰階+二值化
        Mat binaryImg;
        cvtColor(src, resultImg, CV_BGR2GRAY);
        threshold(resultImg, binaryImg, 40, 255, THRESH_BINARY | THRESH_OTSU);
        imshow("binary image", binaryImg);
        //---彩色轉灰階+二值化

        Mat distImg;
        /*
        輪廓距離
        void distanceTransform(InputArray src, OutputArray dst, int distanceType, int maskSize)
            src：輸入圖，8位元單通道(通常為二值化圖)。
            dst：輸出圖，32位元單通道浮點數圖，和src的尺寸相同。
            distanceType：距離型態，可以選擇CV_DIST_L1、CV_DIST_L2或CV_DIST_C。
            maskSize：遮罩尺寸，可以選3、5或CV_DIST_MASK_PRECISE，當 distanceType為CV_DIST_L1或CV_DIST_C，這個參數限制為3(因為3和5的結果相同)。
        */
        distanceTransform(binaryImg, distImg, CV_DIST_L2, 3);
        normalize(distImg, distImg, 0, 1, NORM_MINMAX);
        imshow("distance result", distImg);

        threshold(distImg, distImg, .4, 1, THRESH_BINARY);
        imshow("distance binary image", distImg);
        Mat k1 = Mat::ones(13, 13, CV_8UC1);
        /*
        侵蝕
        erode(const Mat &src, Mat &dst, Mat kernel, Point anchor=Point(-1,-1), int iterations=1)

            src：輸入圖，可以多通道，深度可為CV_8U、CV_16U、CV_16S、CV_32F或CV_64F。
            dst：輸出圖，和輸入圖尺寸、型態相同。
            kernel：結構元素，如果kernel=Mat()則為預設的3×3矩形，越大侵蝕效果越明顯。
            anchor：原點位置，預設為結構元素的中央。
            iterations：執行次數，預設為1次，執行越多次侵蝕效果越明顯。
        */
        erode(distImg, distImg, k1, Point(-1, -1));
        imshow("distance binary_erode image", distImg);

        Mat dist_8u;
        distImg.convertTo(dist_8u, CV_8U);
        vector< vector<Point> > contours;
        findContours(dist_8u, contours, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE, Point(0, 0));

        Mat markers = Mat::zeros(src.size(), CV_32SC1);
        for (size_t i = 0; i < contours.size(); i++)
        {
            drawContours(markers, contours, static_cast<int>(i), Scalar::all(static_cast<int>(i) + 1), -1);
        }
        circle(markers, Point(5, 5), 3, Scalar(255, 255, 255), -1);
        imshow("my markers", markers*1000);

        /*
        OpenCV分水嶺
        void watershed(InputArray image, InputOutputArray markers)

            image：輸入圖，8位元3通道圖。
            markers：輸入輸出標記圖，32位元單通道圖，尺寸必須和image相同。
        */
        watershed(src, markers);
        Mat mark = Mat::zeros(markers.size(), CV_8UC1);

        markers.convertTo(mark, CV_8UC1);

        bitwise_not(mark, mark, Mat());
        imshow("watershed image", mark);

        vector<Vec3b> colors;
        for (size_t i = 0; i < contours.size(); i++)
        {
            int r = theRNG().uniform(0, 255);
            int g = theRNG().uniform(0, 255);
            int b = theRNG().uniform(0, 255);
            colors.push_back(Vec3b((uchar)b, (uchar)g, (uchar)r));
        }

        Mat dst = Mat::zeros(markers.size(), CV_8UC3);
        for (int row = 0; row < markers.rows; row++) {
            for (int col = 0; col < markers.cols; col++) {
                int index = markers.at<int>(row, col);
                if (index > 0 && index <= static_cast<int>(contours.size())) {
                    dst.at<Vec3b>(row, col) = colors[index - 1];
                }
                else {
                    dst.at<Vec3b>(row, col) = Vec3b(0, 0, 0);
                }
            }
        }
        imshow("Final Result", dst);
	}

    waitKey(0);
    Pause();
    return 0;
}
