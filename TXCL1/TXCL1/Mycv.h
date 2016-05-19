#pragma once
#define	C_E 2.718281
#define C_PI 3.141592

struct C_circle
{
	Point2f pos;
	float r;
	float size;
	float wight;
};


class CMycv
{
public:
	CMycv();
	~CMycv();

	//RGB系列API
	Mat RGB_Histogram(Mat* img, int hi, int wi);//三通道直方图
	Mat RGB_Equalization(Mat* img);//三通道直方图均衡
	Mat RGB_Gray(Mat* img,int _type);//RGB转灰度图
	Mat RGB_Extract(Mat* img, int p);//RGB通道提取
	Mat RGB_Synthesis(Mat* r, Mat* g, Mat* b);//3通道RGB合成

	//单通道API
	Mat Histogram(Mat* img, int hi, int wi);//单通道直方图
	Mat Equalization(Mat* img);//灰度图直方图均衡
	Mat Filter_Blur_Line(Mat* img, int size_w, int size_h);//线性滤波模糊
	Mat Filter_Median(Mat* img, int size);//中值滤波
	Mat Filter_Laplasse_operator(Mat* img, int type);//拉布拉斯算子



	//////频率域
	Mat DFT(Mat img);//离散傅里叶变换  返回一个双通道图像（旋转后）
	Mat IDFT(Mat dftimg, int hi, int wi, float min=-1,float max=1);//离散傅里叶反变换

	Mat DFT_AmplitudeSpectrum(Mat dftimg, bool _log=true);//幅度谱
	Mat DFT_PhaseSpectrum(Mat dftimg, bool _log = true);//相位谱
	Mat DFT_RealPart(Mat dftimg, bool _log = true);//实部图
	Mat DFT_ImaginaryPart(Mat dftimg, bool _log = true);//虚部图

	//封装好的空间滤波函数
	Mat DFT_LAPLS(Mat img);//拉普拉斯滤波
	Mat DFT_ILPF(Mat img, float D0);//理想低通滤波
	Mat DFT_BLPF(Mat img, float D0, int n);//布特沃斯低通滤波
	Mat DFT_GLPF(Mat img, float D0);//高斯低通滤波器
	Mat DFT_IHPF(Mat img, float D0);//理想高通滤波器
	Mat DFT_BHPF(Mat img, float D0, int n);//布特沃斯高通滤波器
	Mat DFT_GHPF(Mat img, float D0);//高斯高通滤波器

	//频率域滤波器
	Mat DFT_Filter(Mat dftimg, Mat filter);//滤波器与DFT作用
	Mat DFT_Filter(Mat dftimg, Mat filter_Real, Mat filter_Imaginary);//滤波器与DFT作用
	Mat DFT_ILPF(int hi, int wi, float D0);//理想低通滤波器
	Mat DFT_BLPF(int hi, int wi, float D0,int n);//布特沃斯低通滤波器
	Mat DFT_GLPF(int hi, int wi, float D0);//高斯低通滤波器
	Mat DFT_IHPF(int hi, int wi, float D0);//理想高通滤波器
	Mat DFT_BHPF(int hi, int wi, float D0, int n);//布特沃斯高通滤波器
	Mat DFT_GHPF(int hi, int wi, float D0);//高斯高通滤波器
	Mat DFT_LAPLS(int hi, int wi);//拉不拉斯滤波器

	//逆录滤波器
	Mat DFT_Filter_Inverse(Mat dftimg, Mat filter);//滤波器与DFT逆滤波
	Mat DFT_Filter_Inverse(Mat dftimg, Mat filter_Real, Mat filter_Imaginary);//滤波器与DFT逆滤波
	Mat DFT_Inverse_Wiener(Mat dftimg, Mat filter_dft, float k);//维纳滤波
	Mat DFT_Inverse_Constrained_Least_Squares_Filtering(Mat dftimg, Mat filter_dft, float l);//约束最小二乘方滤波

	//主要内部使用API
	int* Histogram_Group(Mat* img);//直方图数组
	float* Cumulative(int* c, float size);//累积直方图数组
	int GreyValue(Mat* img, bool maxormin);//单通道最灰度值
	Mat Histogram(Mat* img, int hi, int wi, float max);//单通道直方图
	Mat Histogram_Equalization(Mat* img, float* l);//灰度图直方图均衡

	void DFT_Filter_Show(Mat filter, char* name);//显示滤波器

	//空间滤波用通用模板
	int Filter_Median(Mat* img, int posx, int posy, int size);
	Mat Matuchar2float(Mat img);//将Mat默认的UCHAR转换为float便于空间域处理


	//霍夫变换
	Mat HoughCircl(Mat img, float min_r, float max_r, float d_r, float min_angle);
	Mat Filter_Gaussian_Blur(Mat img, int size,float o);
	Mat Canny(Mat img, float g_size, float f_o);
	Mat Canny_get_x(Mat img);//返回X偏导
	Mat Canny_get_y(Mat img);//返回Y偏导
	Mat Canny_get_gradient(Mat x,Mat y);//返回梯度
	Mat Canny_get_position(Mat x, Mat y);//返回方位
	Mat Canny_nonmaximumsuppression(Mat x, Mat y,Mat M, Mat T);//非极大值抑制
	Mat Canny_doublethresholddetection(Mat M,Mat N);//双阈值检测
	void TraceEdge(int y, int x, int nThrLow, Mat* N, Mat* M);

	vector<C_circle> HoughCircl(Mat oimg, Mat img, float min_r, float max_r, float d_r, float min_angle, float circle_size = 5, Scalar co = Scalar(0, 0, 255));
	vector<C_circle> HoughCircl_oneR(Mat *img, float r, float angle, float circle_size = 5, Scalar co = Scalar(0, 0, 255));
	
private:
	void rect(Mat *img, Point sp, Point ep, int co);
	void circle(Mat *img, Point sp, float r, float size,Scalar co);
	float PointDistance(float p1x, float p1y, float p2x, float p2y);
	Mat SChangeImgSize(Mat img, float hi, float wi);//简单的放大缩小


	Mat DFT_Rotate(Mat img);//选在DFT图像
};

//滤波模板