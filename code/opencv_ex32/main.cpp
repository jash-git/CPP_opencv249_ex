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

void Demo_Contours(int, void*);
int main()
{
    /// 创建一个图形
    const int r = 100;
    Mat src = Mat::zeros( Size( 4*r, 4*r ), CV_8UC1 );//二值化的畫布

    /// 绘制一系列点创建一个轮廓:
    vector<Point2f> vert(6);

    vert[0] = Point( 1.5*r, 1.34*r );
    vert[1] = Point( 1*r, 2*r );
    vert[2] = Point( 1.5*r, 2.866*r );
    vert[3] = Point( 2.5*r, 2.866*r );
    vert[4] = Point( 3*r, 2*r );
    vert[5] = Point( 2.5*r, 1.34*r );

    /// 在src内部绘制
    for( int j = 0; j < 6; j++ )
    {
        line( src, vert[j],  vert[(j+1)%6], Scalar( 255 ), 3, 8 );//邊緣繪製白線
    }

    /// 得到轮廓
    vector< vector<Point> > contours;
    vector<Vec4i> hierarchy;
    Mat src_copy = src.clone();

    /*
    OpenCV找輪廓
        void findContours(InputOutputArray image, OutputArrayOfArrays contours, int mode, int method, Point offset=Point())

            image：輸入圖，使用八位元單通道圖，所有非零的像素都會列入考慮，通常為二極化後的圖。
            contours：包含所有輪廓的容器(vector)，每個輪廓都是儲存點的容器(vector)，所以contours的資料結構為vector< vector>。
            hierarchy：可有可無的輸出向量，以階層的方式記錄所有輪廓。
            mode：取得輪廓的模式。
                CV_RETR_EXTERNAL：只取最外層的輪廓。
                CV_RETR_LIST：取得所有輪廓，不建立階層(hierarchy)。
                CV_RETR_CCOMP：取得所有輪廓，儲存成兩層的階層，首階層為物件外圍，第二階層為內部空心部分的輪廓，如果更內部有其餘物件，包含於首階層。
                CV_RETR_TREE：取得所有輪廓，以全階層的方式儲存。
            method：儲存輪廓點的方法，有以下幾種可選擇：
                CV_CHAIN_APPROX_NONE：儲存所有輪廓點。
                CV_CHAIN_APPROX_SIMPLE：對水平、垂直、對角線留下頭尾點，所以假如輪廓為一矩形，只儲存對角的四個頂點。
    */
    findContours( src_copy, contours, hierarchy, RETR_TREE, CHAIN_APPROX_SIMPLE);

    /// 计算到轮廓的距离 [拿整張畫布點來]

    Mat raw_dist( src.size(), CV_32FC1 );//單一像素32浮點數記憶體[存放距離變數]

    for( int j = 0; j < src.rows; j++ )
    {
        for( int i = 0; i < src.cols; i++ )
        {
            /*
            double pointPolygonTest(InputArray contour, Point2f pt, bool measureDist)

                用於判斷一個點是否在輪廓中
                當measureDist設定為true時，若返回值為正，表示點在輪廓內部，返回值為負，表示在輪廓外部，返回值為0，表示在輪廓上。
                當measureDist設定為false時，若返回值為+1，表示點在輪廓內部，返回值為-1，表示在輪廓外部，返回值為0，表示在輪廓上。
            */
            float dist=pointPolygonTest( contours[0], Point2f(i,j), true );
            raw_dist.at<float>(j,i) = dist;
        }
    }

    double minVal; double maxVal;
    /*
    找出整個影像記憶體中的最大和最小值
        void minMaxLoc(InputArray src, double* minVal, double* maxVal=0, Point* minLoc=0, Point* maxLoc=0, InputArray mask=noArray())

        src：輸入圖。
        minVal：極小值，可輸入NULL表示不需要。
        maxVal ：極大值，可輸入NULL表示不需要。
        minLoc：極小值的位置，可輸入NULL表示不需要。
        maxLoc：極大值的位置，可輸入NULL表示不需要。
        mask：可有可無的遮罩。
    */
    minMaxLoc( raw_dist, &minVal, &maxVal, 0, 0, Mat() );
    minVal = abs(minVal);
    maxVal = abs(maxVal);

    /// 图形化的显示距离
    Mat drawImg = Mat::zeros( src.size(), CV_8UC3 );//0~255 RGB 彩色畫布 預設為R=0,G=0,B=0

    for( int j = 0; j < src.rows; j++ )
    {
        for( int i = 0; i < src.cols; i++ )
        {
			float dist = raw_dist.at<float>(j, i);
			if (dist > 0) {
                //若返回值為正，表示點在輪廓內部
				drawImg.at<Vec3b>(j, i)[0] = (uchar)(abs(1.0 - (dist / maxVal)) * 255);//B
			}
			else if (dist < 0) {
			    //返回值為負，表示在輪廓外部
				drawImg.at<Vec3b>(j, i)[2] = (uchar)(abs(1.0 - (dist / minVal)) * 255);//R
			} else {
			    //返回值為0，表示在輪廓上
			    //255-0=255
			    //三個255=白色
				drawImg.at<Vec3b>(j, i)[0] = (uchar)(abs(255 - dist));
				drawImg.at<Vec3b>(j, i)[1] = (uchar)(abs(255 - dist));
				drawImg.at<Vec3b>(j, i)[2] = (uchar)(abs(255 - dist));
			}
        }
     }

    /// 创建窗口显示结果
    char* source_window = "Source";
    namedWindow( source_window, CV_WINDOW_AUTOSIZE );
    imshow( source_window, src );
    namedWindow( "Distance", CV_WINDOW_AUTOSIZE );
    imshow( "Distance", drawImg );

    waitKey(0);
    Pause();
    return 0;
}
