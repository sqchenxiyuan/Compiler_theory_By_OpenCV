#pragma once


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
	Mat Filter_Blur_Line(Mat* img, int size);//线性滤波模糊
	Mat Filter_Median(Mat* img, int size);//中值滤波
	Mat Filter_Laplasse_operator(Mat* img, int type);//拉布拉斯算子
	Mat DFT(Mat img);//离散傅里叶变换
	Mat IDFT(Mat img);//离散傅里叶反变换

	//主要内部使用API
	int* Histogram_Group(Mat* img);//直方图数组
	float* Cumulative(int* c, float size);//累积直方图数组
	int GreyValue(Mat* img, bool maxormin);//单通道最灰度值
	Mat Histogram(Mat* img, int hi, int wi, float max);//单通道直方图
	Mat Histogram_Equalization(Mat* img, float* l);//灰度图直方图均衡

	//滤波用通用模板
	int Filter_Median(Mat* img, int posx, int posy, int size);
private:
	void rect(Mat *img, Point sp, Point ep, int co);
};

//滤波模板