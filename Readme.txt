按照OPENCV教學文件 純C++ 範例練習紀錄

opencv_ex01-單純讀取圖檔、秀圖和顏色反轉
opencv_ex02-讀取圖檔時轉灰階、利用遮罩(mask)將圖像的對比度提高，最後將結果存檔
opencv_ex03-cv::Mat資料型態基本建立和利用指標方式抓取或指定每一個Mat中的元素值
opencv_ex04-圖像單純複製clone、圖像轉換+複製cvtColor、判斷是RGB或者為灰階圖channels、抓取/設定圖像每一彩色像素點的RGB值at<Vec3b>(y, x)、抓取/設定圖像每一灰階像素點的值at<uchar>(y, x)
opencv_ex05-兩張大小(寬、高)相同圖像合成addWeighted
opencv_ex06-創建空白Mat資料空間zerors、判斷是RGB或者為灰階圖channels、抓取/設定圖像每一彩色像素點的RGB值at<Vec3b>(y, x)、抓取/設定圖像每一灰階像素點的值at<uchar>(y, x)、確保值大小範圍為0~255之間saturate_cast<uchar>、調整圖像亮度和對比度屬於像素變換output(x,y)=A*input(x,y)+B
