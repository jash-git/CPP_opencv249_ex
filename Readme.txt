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
		
opencv_ex15-圖像放大pyrUp、彩色轉灰階cvtColor、可調門閥值動態灰階轉二值化threshold(THRESH_TRIANGLE 參數的應用)、基本灰階/二值化圖像邊緣檢測filter2D

		Mat Sobel_X = (Mat_<int>(3, 3) << -1, 0, 1, -2,0,2,-1,0,1);
		
		Mat Sobel_Y = (Mat_<int>(3, 3) << -1, -2, -1, 0,0,0, 1,2,1);
		
		Mat Laplacian = (Mat_<int>(3, 3) << 0, -1, 0, -1, 4, -1, 0, -1, 0);
	
	心得: 四種二值化的效果均不相同，所以這範例非常值得一試
	
opencv_ex16-圖像放大pyrUp、RGB變數Scalar、亂數種子和取亂數RNG、圖像加上邊框(小幅度延伸放大)copyMakeBorder

	copyMakeBorder種類有三種:
		BORDER_REFLECT_101;//外推像素和影像邊界成鏡像映射
		BORDER_REPLICATE;//外推的值和邊緣值相同
		BORDER_CONSTANT;//外推的值為常數，常在仿射變換、透視變換中使用。
		
	心得: 亂數種子和取亂數RNG[發現如果只執行一次，那麼數值會固定]
	
opencv_ex17-圖像放大pyrUp、彩色轉灰階cvtColor、灰階圖像邊緣檢測Sobel(Scharr)、灰階像素點的值at<uchar>(y, x)、灰階像素運算正規化saturate_cast、單純圖像相加add、圖像相加可定義權重addWeighted

    void Scharr(InputArray src, OutputArray dst, int ddepth, int dx, int dy, double scale=1, double delta=0, int borderType=BORDER_DEFAULT)

        或是Sobel(src, dst, ddepth, dx, dy, CV_SCHARR)，兩者效果相同。

        src：輸入圖。
        dst：輸出圖，和輸入圖有相同的尺寸和通道數。
        ddepth：輸出圖的深度，使用方式和Sobel相同。
        dx：x方向的微分階數。
        dy：y方向的微分階數。
        scale：縮放值
        delta：偏移量。
		
    void Sobel(InputArray src, OutputArray dst, int ddepth, int dx, int dy, int ksize=3, double scale=1, double delta=0, int borderType=BORDER_DEFAULT)
        src：輸入圖。
        dst：輸出圖，和輸入圖有相同的尺寸和通道數。
        ddepth：輸出圖的深度，假設輸入圖為CV_8U, 支援CV_8U、CV_16S、CV_32F、CV_64F，假設輸入圖為 CV_16U, 支援CV_16U、CV_32F、CV_64F。
        dx：x方向的微分階數。
        dy：y方向的微分階數。
        ksize：核心，必須為1、3、5或7。
        scale：縮放值。
        delta：偏移量。
		
    計算輸入圖各像素，並將結果轉成8位元圖
        void convertScaleAbs(InputArray src, OutputArray dst, double alpha=1, double beta=0)
        src：輸入圖。
        dst：輸出圖。
        alpha：選擇性的乘法因子。
        beta：選擇性的加法因子。
        此函式主要進行3步驟；1.計算 2.取絕對值 3.轉成無正負號8位元圖	

    用saturate_cast將每次的計算結果限定在合理範圍，以本例來說就是從0到255，超過255會設定成255，小於0會設定成0。
        OpenCV 限定合理範圍：template< … > _Tp saturate_cast(_Tp2 v)
        v：輸入參數，會讓此值在合理範圍。
        saturate_cast使用模板，所以呼叫時要指定像素深度。

    OpenCV影像相加：void addWeighted(InputArray src1, double alpha, InputArray src2, double beta, double gamma, OutputArray dst, int dtype=-1)
        src1：輸入圖。
        alpha：src1的權重。
        src2：輸入圖，和src1的尺寸和通道數相同。
        beta：src2的權重。
        gamma：兩圖相加後再增加的值。
        dst：輸出圖，輸出矩陣和輸入矩陣有相同的尺寸和通道數。
        dtype：可有可無的輸出圖深度。

    OpenCV影像相加：void add(InputArray src1, InputArray src2, OutputArray dst, InputArray mask=noArray(), int dtype=-1)
        src1 ：輸入圖或強度值。
        src2 ：輸入圖或強度值。
        dst：輸出圖，輸出圖和輸入圖有相同的尺寸和通道數。
        mask：可有可無的遮罩，8位元單通道圖，指定那些像素要計算。
        dtype：可有可無的輸出圖深度。

    心得: 
		01.雖然已經學會利用灰階圖像做Sobel要讓結果清晰可見的訣竅就是要用convertScaleAbs，但是如果實際應用應該還是要把圖轉成二值化資料會更少，也會比較好後續運算
		02.Sobel(Scharr)目前測試只能用在灰階圖像，不能用在二值化圖像
		03.所以OPENCV的邊緣檢測SOP: 灰階->濾波(高斯)->邊緣檢測->二值化
		
opencv_ex17_self-自己利用opencv_ex15+opencv_ex17做出可以動態4種二值化之後再進行邊緣檢測的範例

opencv_ex18-圖像放大pyrUp、彩色轉灰階cvtColor、灰階圖像邊緣檢測Laplacian、計算輸入圖各像素，並將結果轉成8位元圖convertScaleAbs、轉二值化threshold [THRESH_OTSU | THRESH_BINARY]

    Otsu流程：
        先計算影像的直方圖
        把直方圖強度大於閾值的像素分成一組，把小於閾值的像素分成另一組。
        分別計算這兩組的組內變異數，並把兩個組內變異數相加。
        將0~255依序當作閾值來計算組內變異數和，總和值最小的就是結果閾值。

    OpenCV自適應閾值二值化
        一樣是用threshold()函式，使用方式也一樣，只是最後一個參數增加CV_THRESH_OTSU，目前otsu只能使用在8位元圖。

        double threshold(InputArray src, OutputArray dst, double thresh, double maxval, int type)

        src：輸入圖，只能輸入單通道，8位元或32位元浮點數影像。
        dst：輸出圖，尺寸大小、深度會和輸入圖相同。
        thresh：閾值。
        maxval：二值化結果的最大值。
        type：二值化操作型態，共有THRESH_BINARY、THRESH_BINARY_INV、THRESH_TRUNC、THRESH_TOZERO、THRESH_TOZERO_INV五種。
        type從上述五種結合CV_THRESH_OTSU，類似寫成：THRESH_BINARY | CV_THRESH_OTSU

opencv_ex19-圖像放大pyrUp、彩色轉灰階cvtColor、灰階圖像可調式邊緣檢測Canny、二值化圖像反向輸出

    OpenCV canny
    void Canny(InputArray image, OutputArray edges, double threshold1, double threshold2, int apertureSize=3, bool L2gradient=false)

        src：輸入圖，單通道8位元圖。
        dst：輸出圖，尺寸、型態和輸入圖相同。
        threshold1：第一個閾值。
        threshold2：第二個閾值。
        apertureSize ：Sobel算子的核心大小。
        L2gradient ：梯度大小的算法，預設為false。

opencv_ex20-圖像縮小pyrDown、灰階圖像可調式邊緣檢測Canny、圖像轉換+複製cvtColor、直線偵測HoughLinesP、畫線函數line

    OpenCV 直線偵測
        void HoughLinesP(InputArray image, OutputArray lines, double rho, double theta, int threshold, double minLineLength=0, double maxLineGap=0)

        image：輸入圖，8位元單通道二值化圖。
        lines：將所有線的資料存在vector< Vec4i >，Vec4i為每個線段的資料，分別有x1、y1、x2、y2這四個值，(x1，y1)和(x2，y2)分別表示線段的頭尾頂點。
        rho：距離解析度，越小表示定位要求越準確，但也較易造成應該是同條線的點判為不同線。 1
        theta：角度解析度，越小表示角度要求越準確，但也較易造成應該是同條線的點判為不同線。 CV_PI/180
        threshold：累積個數閾值，超過此值的線才會存在lines這個容器內。 10
        minLineLength ：線段最短距離，超過此值的線才會存在lines這個容器內。 0
        maxLineGap：最大間隔。 10
		
opencv_ex21-灰階圖像可調式邊緣檢測Canny、圖像複製clone()、圖像複製copyTo(...)、偵測圓HoughCircles、畫圓circle、畫筆顏色變數Scalar

    OpenCV 偵測圓
        void HoughCircles(InputArray image, OutputArray circles, int method, double dp, double minDist, double param1=100, doubleparam2=100, int minRadius=0, int maxRadius=0)

        image：輸入圖，8位元單通道圖。
        circles：以vector< Vec3f >記錄所有圓的資訊，每個Vec3f紀錄一個圓的資訊，包含3個浮點數資料，分別表示x、y、radius。
        method：偵測圓的方法，目前只能使用CV_HOUGH_GRADIENT。
        dp：偵測解析度倒數比例，假設dp=1，偵測圖和輸入圖尺寸相同，假設dp=2，偵測圖長和寬皆為輸入圖的一半。
        minDist：圓彼此間的最短距離，太小的話可能會把鄰近的幾個圓視為一個，太大的話可能會錯過某些圓。
        param1：圓偵測內部會呼叫Canny()尋找邊界，param1就是Canny()的高閾值，低閾值自動設為此值的一半。
        param2：計數閾值，超過此值的圓才會存入circles。-調整重要參數
        minRadius：最小的圓半徑。
        maxRadius：最大的圓半徑。
		
opencv_ex22-圖像放大pyrUp、創建空白Mat資料空間zerors、創建空白Mat資料空間create、幾何變換remap
     
    OpenCV重映射
        void remap(InputArray src, OutputArray dst, InputArray map1, InputArray map2, int interpolation, int borderMode=BORDER_CONSTANT, const Scalar& borderValue=Scalar())

        src：輸入圖。
        dst：輸出圖，型態和輸入圖相同。
        map1：第一個輸入的映射表，型態可為CV_16SC2、CV_32FC1或CV_32FC2，尺寸和輸入圖相同，映射表的值代表的是輸入圖此像素位置要轉移去的新x座標。
        map2：第二個輸入的映射表，型態可為CV_16UC1或 CV_32FC1，尺寸和輸入圖相同，映射表的值代表的是輸入圖此像素位置要轉移去的新y座標。。
        interpolation：內插型態。
        borderMode：邊界模式，預設為BORDER_CONSTANT。
        borderValue：邊界外推值，預設強度為0。            