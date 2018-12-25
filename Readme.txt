按照OPENCV教學文件 純C++ 範例練習紀錄

opencv_ex01-單純讀取圖檔、秀圖和顏色反轉

opencv_ex02-讀取圖檔時轉灰階IMREAD_GRAYSCALE、利用遮罩(mask)將圖像的對比度提高，最後將結果存檔

opencv_ex03-cv::Mat資料型態基本建立和利用指標方式抓取或指定每一個Mat中的元素值

opencv_ex04-圖像單純複製clone、圖像轉換+複製cvtColor、判斷是RGB或者為灰階圖channels、抓取/設定圖像每一彩色像素點的RGB值at<Vec3b>(y, x)、抓取/設定圖像每一灰階像素點的值at<uchar>(y, x)

opencv_ex05-兩張大小(寬、高)相同圖像合成addWeighted

opencv_ex06-創建空白Mat資料空間zerors、判斷是RGB或者為灰階圖channels、抓取/設定圖像每一彩色像素點的RGB值at<Vec3b>(y, x)、抓取/設定圖像每一灰階像素點的值at<uchar>(y, x)、確保值大小範圍為0~255之間saturate_cast<uchar>、調整圖像亮度和對比度屬於像素變換output(x,y)=A*input(x,y)+B

opencv_ex07-創建空白Mat資料空間zerors、繪製線段line、繪製矩形rectangle、繪製橢圓和圓弧ellipse、繪製圓型circle、繪製填色封閉任意形狀fillPoly、OPENCV亂數種子和取亂數RNG、OPENCV畫筆顏色變數Scalar 

opencv_ex08-利用均值模糊blur、高斯模糊GaussianBlur目的為了給圖像預處理時候減低噪聲(雜訊)

opencv_ex09-利用中值濾波medianBlur、高斯雙邊模糊bilateralFilter、最後利用提高對比度遮罩(mask)運算來補強圖像

	中值對椒鹽噪聲有很好的抑製作用
	
	均值模糊無法克服邊緣像素信息丟失缺陷。原因是均值濾波是基於平均權重

	高斯模糊部分克服了該缺陷，但是無法完全避免，因為沒有考慮像素值的不同

	高斯雙邊模糊 – 是邊緣保留的濾波方法，避免了邊緣信息丟失，保留了圖像輪廓不變

opencv_ex10-讀取圖檔時轉灰階IMREAD_GRAYSCALE、設定門閥值灰階轉二值化threshold、腐蝕(侵蝕)erode、膨脹dilate、得到要進行侵蝕或膨脹的模板getStructuringElement

	膨脹->白色越多
	
	腐蝕->黑色越多
		
opencv_ex11-讀取圖檔時轉灰階IMREAD_GRAYSCALE、可調門閥值動態灰階轉二值化threshold、形態學操作morphologyEx
	
	形態學操作種類:
		CV_MOP_OPEN:先腐蝕後膨脹-可以去掉小的對象，假設對像是前景色，背景是黑色
		CV_MOP_CLOSE:先膨脹後腐蝕-可以填充小的洞（fill hole），假設對像是前景色，背景是黑色
		CV_MOP_GRADIENT:膨脹減去腐蝕-又稱為基本梯度（其它還包括-內部梯度、方向梯度）
		CV_MOP_TOPHAT:頂帽 是原圖像與開操作之間的差值圖像
		CV_MOP_BLACKHAT:黑帽 是閉操作圖像與源圖像的差值圖像
				
	心得:對人像而言-只有CV_MOP_GRADIENT比較有用,size(3,3)
	
opencv_ex12-讀取圖檔時轉灰階IMREAD_GRAYSCALE、彩色轉灰階cvtColor、區域門閥值灰階轉二值化adaptiveThreshold、利用開操作偵測直線、利用開操作偵測橫線、利用開操作實現簡易驗證碼圖像過濾保留文字

opencv_ex13-彩色轉灰階cvtColor、圖像放大pyrUp、圖像縮小pyrDown、高斯平滑濾波GaussianBlur、圖像相減subtract、圖像歸一化顯示normalize
	高斯不同(Difference of Gaussian-DOG)
		定義：就是把同一張圖像在不同的參數下做高斯模糊之後的結果相減，得到的輸出圖像。稱為高斯不同(DOG)
		高斯不同是圖像的內在特徵，在灰度圖像增強、角點檢測中經常用到。
	
	心得:對人像而言-DOG可以精準抓出圖像邊緣
	
opencv_ex14-圖像放大pyrUp、彩色轉灰階cvtColor、可調門閥值動態灰階轉二值化threshold(THRESH_TRIANGLE 參數的應用)
	
	心得:
		THRESH_TRIANGLE 在249沒有這個參數，但是可以直接用16這個數值取代
		type_value=0就會是opencv_ex11的效果(傳統書本教的二值化)