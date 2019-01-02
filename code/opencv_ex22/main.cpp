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

Mat dst, map_x, map_y;
int index = 0;
void update_map(void);

void Pause()
{
    printf("Press Enter key to continue...");
    fgetc(stdin);
}
int main()
{
    const char* OUTPUT_TITLE = "remap demo";

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

        namedWindow("Lena_original", CV_WINDOW_AUTOSIZE);
        imshow("Lena_original", src);

        namedWindow(OUTPUT_TITLE, CV_WINDOW_AUTOSIZE);

        map_x.create(src.size(), CV_32FC1);
        map_y.create(src.size(), CV_32FC1);
        dst=Mat::zeros(src.size(),src.type());

        int c = 0;
        while (true) {
            c = waitKey(500);
            if ((char)c == 27) {//ESC
                break;
            }
            index = c % 4;
            printf("%d -> %d\n",c,index);
            update_map();
            /*
            幾何變換(remap)
            OpenCV重映射
            void remap(InputArray src, OutputArray dst, InputArray map1, InputArray map2, int interpolation, int borderMode=BORDER_CONSTANT, const Scalar& borderValue=Scalar())

            src：輸入圖。
            dst：輸出圖，型態和輸入圖相同。
            map1：第一個輸入的映射表，型態可為CV_16SC2、CV_32FC1或CV_32FC2，尺寸和輸入圖相同，映射表的值代表的是輸入圖此像素位置要轉移去的新x座標。
            map2：第二個輸入的映射表，型態可為CV_16UC1或 CV_32FC1，尺寸和輸入圖相同，映射表的值代表的是輸入圖此像素位置要轉移去的新y座標。。
            interpolation：內插型態。
            borderMode：邊界模式，預設為BORDER_CONSTANT。
            borderValue：邊界外推值，預設強度為0。
            */
            remap(src, dst, map_x, map_y, INTER_LINEAR, BORDER_CONSTANT, Scalar(0, 255, 255));
            imshow(OUTPUT_TITLE, dst);
        }
    }

    waitKey(0);
    Pause();
    return 0;
}

void update_map(void) {
	for (int row = 0; row < src.rows; row++) {//高度 X
		for (int col = 0; col < src.cols; col++) {//寬度 Y
			switch (index) {
			case 0://縮小一半
				if (col > (src.cols * 0.25) && col <= (src.cols*0.75) && row > (src.rows*0.25) && row <= (src.rows*0.75)) {
					map_x.at<float>(row, col) = 2 * (col - (src.cols*0.25));
					map_y.at<float>(row, col) = 2 * (row - (src.rows*0.25));
				}
				else {
					map_x.at<float>(row, col) = 0;
					map_y.at<float>(row, col) = 0;
				}
				break;
			case 1://X反轉
				map_x.at<float>(row, col) = (src.cols - col - 1);
				map_y.at<float>(row, col) = row;
				break;
			case 2://Y反轉
				map_x.at<float>(row, col) = col;
				map_y.at<float>(row, col) = (src.rows - row - 1);
				break;
			case 3://XY反轉
				map_x.at<float>(row, col) = (src.cols - col - 1);
				map_y.at<float>(row, col) = (src.rows - row - 1);
				break;
			}

		}
	}
}
