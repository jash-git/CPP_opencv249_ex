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
    cv::Mat N(2,2,CV_8UC3, Scalar(0,0,255));
    cout << "N = " << endl << " " << N << endl << endl;

    Mat M;
    M.create(4, 3, CV_8UC2);
    M = Scalar(0,255);
    cout << "M = " << endl << " " << M << endl << endl;

    int channels = M.channels();
    int rows = M.rows;
    int cols = M.cols;
    printf("M rows=%d,cols=%d,channels=%d\n",rows,cols,channels);

    for(int i=0;i<rows;i++)//0~3
    {
        uchar* NowRowpoint = M.ptr<uchar>(i);
        for(int j=0;j<(cols*channels);j++)//0~5
        {
            if(j<(cols*channels-1))
            {
                printf("%4d,", *(NowRowpoint+j));
            }
            else
            {
                printf("%4d;", *(NowRowpoint+j));
            }
        }
        printf("\n");
    }
    printf("\n");

    Mat C = (Mat_<double>(3, 3) << 0, -1, 0, -1, 5, -1, 0, -1, 0);
    cout << "C = " << endl << " " << C << endl << endl;
    channels = C.channels();
    rows = C.rows;
    cols = C.cols;
    printf("C rows=%d,cols=%d,channels=%d\n",rows,cols,channels);
    for(int i=0;i<rows;i++)//0~2
    {
        double* NowRowpoint = C.ptr<double>(i);
        for(int j=0;j<(cols*channels);j++)//0~2
        {
            if(j<(cols*channels-1))
            {
                printf("%2.0f,", *(NowRowpoint+j));//printf("%1.0f,", *(NowRowpoint+j));
            }
            else
            {
                printf("%2.0f;", *(NowRowpoint+j));//printf("%1.0f;", *(NowRowpoint+j));
            }
        }
        printf("\n");
    }
    printf("\n");

    Mat C1 = (Mat_<double>(3, 3) << 0, 0, 0, 0, 0, 0, 0, 0, 0);
    cout << "init C1 = " << endl << " " << C1 << endl << endl;
    channels = C1.channels();
    rows = C1.rows;
    cols = C1.cols;
    for(int i=0;i<rows;i++)//0~2
    {
        double* NowRowpoint = C1.ptr<double>(i);
        for(int j=0;j<(cols*channels);j++)//0~2
        {
            *(NowRowpoint+j)=-1;
        }
    }
    Mat C2=C1.clone();
    cout << "set C2 = " << endl << " " << C2 << endl << endl;

    Pause();

    return 0;
}
