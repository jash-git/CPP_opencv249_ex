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

opencv_ex23-圖像放大pyrUp、彩色轉灰階cvtColor、直方圖拉伸(直方圖等化)equalizeHist

    使用時機:我們可透過拉伸直方圖，使直方圖覆蓋所有強度範圍，這種方法的確能提高影像對比度，但是在多數情況，影像模糊不是因為過窄的強度範圍，而是某區間的像素強度比例過高，這時可以製作一個映射表，使得調整之後的影像，能平均使用所有的強度，進而增加影像的整體對比度。

    OpenCV直方圖等化
        void equalizeHist(InputArray src, OutputArray dst)

        src：輸入圖，8位元單通道圖。
        dst：輸出圖，和輸入圖尺寸、型態相同。
        equalizeHist()函式可得到直方圖等化後的影像，以下為流程，OpenCV已將流程封裝好，使用時只要直接呼叫equalizeHist()函式即可：

        計算輸入圖的直方圖。
        將直方圖歸一到所有bin的總合為255。
        計算直方圖累計表。
        用直方圖累計表完成各強度的映射，所以假設強度30所累積的比例為20%，映射的強度即為255*0.2，由於我們直方圖歸一化到255，所以假設強度30所累積的值為20，映射的強度即為20。

opencv_ex24-圖像放大pyrUp、將一張RGB的圖片拆成三張單元色的的圖split、直方圖計算calcHist、如果圖形很大那麼直方圖的點數很多這時就要把值歸一化normalize、四捨五入相關函數

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

    四捨五入相關函數		
        cvRound()：返回跟參數最接近的整數值，即四捨五入；
        cvFloor()：返回不大於參數的最大整數值，即向下取整；
        cvCeil()：返回不小於參數的最小整數值，即向上取整；
		
opencv_ex25-圖像放大pyrUp、彩色或灰階轉HSV格式cvtColor、多變量直方圖變數MatND、HSV多變量直方圖計算calcHist、如果圖形很大那麼直方圖的點數很多這時就要把值歸一化normalize、畫面上寫文字putText
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

    OpenCV直方圖比較
        double compareHist(InputArray H1, InputArray H2, int method)

        H1：第一個直方圖。
        H2：第二個直方圖，須和第一個直方圖尺寸相同。
        method：比較方法，有以下四種方法可選擇，不論選擇何種，皆會返回一個比較值：
            CV_COMP_CORREL：信號處理中的歸一化互相關方法，N為bin的總個數
            CV_COMP_CHISQR：歸一化的平方和
            CV_COMP_INTERSECT ：比較每個直方圖bin的值，總和較小的那個，也就是假如兩個直方圖沒有共同的值，計算結果為0，完全相同的直方圖，返回值等於像素的個數。
            CV_COMP_BHATTACHARYYA：統計學中用於評估兩個概率分布相似性
			
opencv_ex26-圖像放大pyrUp、彩色或灰階轉HSV格式cvtColor、畫矩形rectangle、直方圖反投影calcBackProject
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

    畫矩形
        void rectangle(Mat& img, Point pt1, Point pt2, const Scalar& color, int thickness=1, int lineType=8, int shift=0)

        img：輸入圖，矩形會畫在上面。
        pt1：矩形頂點。
        pt2：矩形頂點，pt1的對角邊
        color：矩形的顏色。
        thickness：矩形的邊線寬度，輸入負值或CV_FILLED代表填滿矩形。
        lineType：通道型態，可輸入8、4、CV_AA： 8->8通道連結。 4->4通道連結。 CV_AA->消除鋸齒(antialiased line)，消除顯示器畫面線邊緣的凹凸鋸齒。		
		
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

opencv_ex27-影像模板比對matchTemplate、歸一化函式normalize、計算比對後目標影像的位置minMaxLoc、畫矩形rectangle
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

    當我們得到比較圖後，根據由比較方式，選擇比較圖最小或最大值的地方，就是目標影像的位置。
        void minMaxLoc(InputArray src, double* minVal, double* maxVal=0, Point* minLoc=0, Point* maxLoc=0, InputArray mask=noArray())

        src：輸入圖。
        minVal：極小值，可輸入NULL表示不需要。
        maxVal ：極大值，可輸入NULL表示不需要。
        minLoc：極小值的位置，可輸入NULL表示不需要。
        maxLoc：極大值的位置，可輸入NULL表示不需要。
        mask：可有可無的遮罩。
		
	畫矩形
        void rectangle(Mat& img, Point pt1, Point pt2, const Scalar& color, int thickness=1, int lineType=8, int shift=0)

        img：輸入圖，矩形會畫在上面。
        pt1：矩形頂點。
        pt2：矩形頂點，pt1的對角邊
        color：矩形的顏色。
        thickness：矩形的邊線寬度，輸入負值或CV_FILLED代表填滿矩形。
        lineType：通道型態，可輸入8、4、CV_AA： 8->8通道連結。 4->4通道連結。 CV_AA->消除鋸齒(antialiased line)，消除顯示器畫面線邊緣的凹凸鋸齒。		

opencv_ex27_self-影像模板比對matchTemplate、歸一化函式normalize、自己抓取matchTemplate的結果找出相似度大於0.9實現多項目比對	
    影像模板比對matchTemplate
        method：比較方法，有以下六種方法可選擇：
            method=CV_TM_SQDIFF
            method=CV_TM_SQDIFF_NORMED
            method=CV_TM_CCORR
            method=CV_TM_CCORR_NORMED
            method=CV_TM_CCOEFF
            method=CV_TM_CCOEFF_NORMED

        當我們的參數為CV_TM_SQDIFF時，計算結果較小時相似度較高，當我們參數為CV_TM_CCORR、CV_TM_CCOEF時，計算結果較大時相似度較高。	
	
	備註:程式碼因為寫3導致要找接近1的數 -> >0.9 反之 如果寫0就要找接近0的數 -> <0.1
	
opencv_ex28-彩色或灰階轉HSV格式cvtColor、灰階圖像可調式邊緣檢測Canny、從邊緣圖找輪廓的點findContours、產生亂數RNG、畫輪廓線drawContours

    OpenCV canny
        void Canny(InputArray image, OutputArray edges, double threshold1, double threshold2, int apertureSize=3, bool L2gradient=false)

            src：輸入圖，單通道8位元圖。
            dst：輸出圖，尺寸、型態和輸入圖相同。
            threshold1：第一個閾值。
            threshold2：第二個閾值。
            apertureSize ：Sobel算子的核心大小。
            L2gradient ：梯度大小的算法，預設為false。
		
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
				
    OpenCV畫輪廓線
        void drawContours(InputOutputArray image, InputArrayOfArrays contours, int contourIdx, const Scalar& color, int thickness=1, int lineType=8, InputArray hierarchy=noArray(), int maxLevel=INT_MAX, Point offset=Point())

            image：輸入輸出圖，會將輪廓畫在此影像上。
            contours：包含所有輪廓的容器(vector)，也就是findContours()所找到的contours。
            contourIdx：指定畫某個輪廓。
            color：繪製的顏色。
            lineType：繪製的線條型態。
            hierarchy：輪廓階層，也就是findContours()所找到的hierarchy。
            maxLevel：最大階層的輪廓，可以指定想要畫的輪廓，有輸入hierarchy時才會考慮，輸入的值代表繪製的層數。				
			
opencv_ex29-彩色或灰階轉HSV格式cvtColor、灰階圖像可調式邊緣檢測Canny、從邊緣圖找輪廓的點findContours、產生亂數RNG、凸殼convexHull、畫輪廓線drawContours

    OpenCV canny
        void Canny(InputArray image, OutputArray edges, double threshold1, double threshold2, int apertureSize=3, bool L2gradient=false)

            src：輸入圖，單通道8位元圖。
            dst：輸出圖，尺寸、型態和輸入圖相同。
            threshold1：第一個閾值。
            threshold2：第二個閾值。
            apertureSize ：Sobel算子的核心大小。
            L2gradient ：梯度大小的算法，預設為false。
		
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

    凸殼(Convex Hull)是一個計算幾何中的概念，簡單的說，在給定二維平面上的點集合，凸殼就是將最外層的點連接起來的凸多邊型，它能包含點集合中的所有點，在影像處理中，通常是找到某個物件後，用來填補空隙，或者是進一步的進行物件辨識。
        void convexHull(InputArray points, OutputArray hull, bool clockwise=false, bool returnPoints=true)

        points：輸入資訊，可以為包含點的容器(vector)或是Mat。
        hull：輸出資訊，包含點的容器(vector)。
        lockwise：方向旗標，如果true是順時針，false是逆時針。
			
    OpenCV畫輪廓線
        void drawContours(InputOutputArray image, InputArrayOfArrays contours, int contourIdx, const Scalar& color, int thickness=1, int lineType=8, InputArray hierarchy=noArray(), int maxLevel=INT_MAX, Point offset=Point())

            image：輸入輸出圖，會將輪廓畫在此影像上。
            contours：包含所有輪廓的容器(vector)，也就是findContours()所找到的contours。
            contourIdx：指定畫某個輪廓。
            color：繪製的顏色。
            lineType：繪製的線條型態。
            hierarchy：輪廓階層，也就是findContours()所找到的hierarchy。
            maxLevel：最大階層的輪廓，可以指定想要畫的輪廓，有輸入hierarchy時才會考慮，輸入的值代表繪製的層數。	

opencv_ex30-彩色或灰階轉HSV格式cvtColor、灰階圖像可調式邊緣檢測Canny、從邊緣圖找輪廓的點findContours、輪廓點進行多邊形擬合approxPolyDP、求包覆最小斜矩形minAreaRect、求包覆圓形minEnclosingCircle、橢圓擬合fitEllipse、最小面積矩形擬合minAreaRect、產生亂數RNG、凸殼convexHull、畫輪廓線drawContours

    OpenCV canny
        void Canny(InputArray image, OutputArray edges, double threshold1, double threshold2, int apertureSize=3, bool L2gradient=false)

            src：輸入圖，單通道8位元圖。
            dst：輸出圖，尺寸、型態和輸入圖相同。
            threshold1：第一個閾值。
            threshold2：第二個閾值。
            apertureSize ：Sobel算子的核心大小。
            L2gradient ：梯度大小的算法，預設為false。
		
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

    凸殼(Convex Hull)是一個計算幾何中的概念，簡單的說，在給定二維平面上的點集合，凸殼就是將最外層的點連接起來的凸多邊型，它能包含點集合中的所有點，在影像處理中，通常是找到某個物件後，用來填補空隙，或者是進一步的進行物件辨識。
        void convexHull(InputArray points, OutputArray hull, bool clockwise=false, bool returnPoints=true)

        points：輸入資訊，可以為包含點的容器(vector)或是Mat。
        hull：輸出資訊，包含點的容器(vector)。
        lockwise：方向旗標，如果true是順時針，false是逆時針。
			
    OpenCV畫輪廓線
        void drawContours(InputOutputArray image, InputArrayOfArrays contours, int contourIdx, const Scalar& color, int thickness=1, int lineType=8, InputArray hierarchy=noArray(), int maxLevel=INT_MAX, Point offset=Point())

            image：輸入輸出圖，會將輪廓畫在此影像上。
            contours：包含所有輪廓的容器(vector)，也就是findContours()所找到的contours。
            contourIdx：指定畫某個輪廓。
            color：繪製的顏色。
            lineType：繪製的線條型態。
            hierarchy：輪廓階層，也就是findContours()所找到的hierarchy。
            maxLevel：最大階層的輪廓，可以指定想要畫的輪廓，有輸入hierarchy時才會考慮，輸入的值代表繪製的層數。

    對圖像輪廓點進行多邊形擬合-approxPolyDP
        void approxPolyDP(InputArray curve, OutputArray approxCurve, double epsilon, bool closed)

        參數詳解;
        InputArray curve:一般是由圖像的輪廓點組成的點集
        OutputArray approxCurve：表示輸出的多邊形點集
        double epsilon：主要表示輸出的精度，就是另個輪廓點之間最大距離數，5,6,7，，8，，,,，
        bool closed：表示輸出的多邊形是否封閉

    求包覆最小斜矩形
        RotatedRect minAreaRect(InputArray points)

        points：輸入資訊，可以為包含點的容器(vector)或是Mat。
        返回包覆輸入資訊的最小斜矩形。

    求包覆圓形
        void minEnclosingCircle(InputArray points, Point2f& center, float& radius)

        points：輸入資訊，可以為包含點的容器(vector)或是Mat。
        center：包覆圓形的圓心。
        radius：包覆圓形的半徑。

    橢圓擬合

        RotatedRect fitEllipse(InputArray points)
        輸入：二維點集，要求擬合的點至少為6個點。存儲在std::vector<> or Mat		
		
    最小面積矩形擬合

        RotatedRect minAreaRect(InputArray points)
        InputArray points：表示輸入的點集	
		
opencv_ex31-彩色或灰階轉HSV格式cvtColor、灰階圖像可調式邊緣檢測Canny、從邊緣圖找輪廓的點findContours、產生亂數RNG、畫輪廓線drawContours、從輪廓的點計算矩moments、計算矩後求質心、從輪廓的點求面積contourArea、從輪廓的點求周長arcLength、從輪廓的點比對圖形相似度matchShape

    OpenCV canny
        void Canny(InputArray image, OutputArray edges, double threshold1, double threshold2, int apertureSize=3, bool L2gradient=false)

            src：輸入圖，單通道8位元圖。
            dst：輸出圖，尺寸、型態和輸入圖相同。
            threshold1：第一個閾值。
            threshold2：第二個閾值。
            apertureSize ：Sobel算子的核心大小。
            L2gradient ：梯度大小的算法，預設為false。
		
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
				
    OpenCV畫輪廓線
        void drawContours(InputOutputArray image, InputArrayOfArrays contours, int contourIdx, const Scalar& color, int thickness=1, int lineType=8, InputArray hierarchy=noArray(), int maxLevel=INT_MAX, Point offset=Point())

            image：輸入輸出圖，會將輪廓畫在此影像上。
            contours：包含所有輪廓的容器(vector)，也就是findContours()所找到的contours。
            contourIdx：指定畫某個輪廓。
            color：繪製的顏色。
            lineType：繪製的線條型態。
            hierarchy：輪廓階層，也就是findContours()所找到的hierarchy。
            maxLevel：最大階層的輪廓，可以指定想要畫的輪廓，有輸入hierarchy時才會考慮，輸入的值代表繪製的層數。				
	

    計算矩
    Moments moments(InputArray array, bool binaryImage=false)

        array：來源圖，可以輸入8位元單通道圖、浮點數2維陣列，或1xN、Nx1的Point或Point2f陣列。
        binaryImage：影像設定，只有array為影像時才有效果，如果設定為true，所有非零的像素都列入計算。
        可從Moments計算質心位置。
        假設返回一個Moments mu，我們可依據下式，從mu計算質心位置，m10、m00、m01、m00都是Moments的類別成員。	

    計算面積
    double contourArea(InputArray contour, bool oriented=false)

        contour：輸入輪廓，一個含有2維點的vector。
        oriented：輪廓方向，如果設為ture的話除了面積還會記錄方向，順時鐘和逆時鐘會有正負號的差異，預設為false，不論輪廓方向都返回正的面積值。

    計算周長：
    double arcLength(InputArray curve, bool closed)

        curve：輸入輪廓，一個含有2維點的vector。
        closed：輪廓封閉，指定curve是否封閉，

    從輪廓的點比對圖形相似度
    函數matchShape() 可以幫我們比較兩個形狀或輪廓的相似度。如果返回值越小
    	https://docs.opencv.org/2.4/modules/imgproc/doc/structural_analysis_and_shape_descriptors.html#double%20matchShapes(InputArray%20contour1,%20InputArray%20contour2,%20int%20method,%20double%20parameter)
		
opencv_ex32-建立二值化的畫布Mat::zeros( Size(W,H), CV_8UC1)、畫線line、二值化圖找輪廓的點findContours、輪廓和點距離pointPolygonTest、找出整個影像記憶體中的最大和最小值minMaxLoc、建立彩色的畫布Mat::zeros( src.size(), CV_8UC3 );

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
    
	OpenCV輪廓和點距離
        double pointPolygonTest(InputArray contour, Point2f pt, bool measureDist)

            用於判斷一個點是否在輪廓中
            當measureDist設定為true時，若返回值為正，表示點在輪廓內部，返回值為負，表示在輪廓外部，返回值為0，表示在輪廓上。
            當measureDist設定為false時，若返回值為+1，表示點在輪廓內部，返回值為-1，表示在輪廓外部，返回值為0，表示在輪廓上。
			
    找出整個影像記憶體中的最大和最小值
        void minMaxLoc(InputArray src, double* minVal, double* maxVal=0, Point* minLoc=0, Point* maxLoc=0, InputArray mask=noArray())

        src：輸入圖。
        minVal：極小值，可輸入NULL表示不需要。
        maxVal ：極大值，可輸入NULL表示不需要。
        minLoc：極小值的位置，可輸入NULL表示不需要。
        maxLoc：極大值的位置，可輸入NULL表示不需要。
        mask：可有可無的遮罩。			