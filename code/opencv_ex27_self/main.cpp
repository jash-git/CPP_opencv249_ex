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

///多目标模板匹配-https://blog.csdn.net/abc8730866/article/details/68487029
int main()
{

	Mat srcImg = imread("input.png");
	if (!srcImg.data)
    {
		printf("could not load image...\n");
	}
    else
    {
        Mat tempImg = imread("temp.png");
        //1.构建结果图像resultImg(注意大小和类型)
        //如果原图(待搜索图像)尺寸为W x H, 而模版尺寸为 w x h, 则结果图像尺寸一定是(W-w+1)x(H-h+1)
        //结果图像必须为单通道32位浮点型图像
        int width = srcImg.cols - tempImg.cols + 1;
        int height = srcImg.rows - tempImg.rows + 1;
        Mat resultImg(Size(width, height), CV_32FC1);
        //2.模版匹配
        matchTemplate(srcImg, tempImg, resultImg, 3);
        imshow("result", resultImg);
        //3.正则化(归一化到0-1)
        normalize(resultImg, resultImg, 0, 1, NORM_MINMAX, -1);
        //4.遍历resultImg，给定筛选条件，筛选出前几个匹配位置
        int tempX = 0;
        int tempY = 0;
        char prob[10] = { 0 };
        //4.1遍历resultImg
        for (int i = 0 ; i<resultImg.rows;i++)
        {
            for (int j = 0; j<resultImg.cols; j++)
            {
                //4.2获得resultImg中(j,x)位置的匹配值matchValue
                double matchValue = resultImg.at<float>(i, j);
                sprintf(prob, "%.2f", matchValue);
                //4.3给定筛选条件
                //条件1:概率值大于0.9
                //条件2:任何选中的点在x方向和y方向上都要比上一个点大5(避免画边框重影的情况)
                if (matchValue > 0.9&& abs(i-tempY)>5&&abs(j-tempX)>5)
                {
                    //5.给筛选出的点画出边框和文字
                    rectangle(srcImg, Point(j,i), Point(j + tempImg.cols, i + tempImg.rows), Scalar(0, 255, 0), 1, 8);
                    putText(srcImg, prob, Point(j, i+100),CV_FONT_BLACK,1,Scalar(0,0,255),1);
                    printf("%s\n",prob);
                    tempX = j;
                    tempY = i;
                }
            }
        }
        imshow("srcImg", srcImg);
        imshow("template", tempImg);
    }
    waitKey(0);
    Pause();
    return 0;
}
