#pragma once
#define	C_E 2.718281
#define C_PI 3.141592

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

	Mat DFT_AmplitudeSpectrum(Mat dftimg);//幅度谱
	Mat DFT_PhaseSpectrum(Mat dftimg);//相位谱
	Mat DFT_RealPart(Mat dftimg,bool _log);//实部图
	Mat DFT_ImaginaryPart(Mat dftimg, bool log);//虚部图

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
	Mat DFT_ILPF(int hi, int wi, float D0);//理想低通滤波器
	Mat DFT_BLPF(int hi, int wi, float D0,int n);//布特沃斯低通滤波器
	Mat DFT_GLPF(int hi, int wi, float D0);//高斯低通滤波器
	Mat DFT_IHPF(int hi, int wi, float D0);//理想高通滤波器
	Mat DFT_BHPF(int hi, int wi, float D0, int n);//布特沃斯高通滤波器
	Mat DFT_GHPF(int hi, int wi, float D0);//高斯高通滤波器
	Mat DFT_LAPLS(int hi, int wi);//拉不拉斯滤波器

	//主要内部使用API
	int* Histogram_Group(Mat* img);//直方图数组
	float* Cumulative(int* c, float size);//累积直方图数组
	int GreyValue(Mat* img, bool maxormin);//单通道最灰度值
	Mat Histogram(Mat* img, int hi, int wi, float max);//单通道直方图
	Mat Histogram_Equalization(Mat* img, float* l);//灰度图直方图均衡

	void DFT_Filter_Show(Mat filter, char* name);//显示滤波器

	//空间滤波用通用模板
	int Filter_Median(Mat* img, int posx, int posy, int size);
private:
	void rect(Mat *img, Point sp, Point ep, int co);
	float PointDistance(float p1x, float p1y, float p2x, float p2y);


	Mat DFT_Rotate(Mat img);//选在DFT图像
};

//滤波模板