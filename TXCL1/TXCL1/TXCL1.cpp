// TXCL1.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"


void draw_zft(int r[], int g[], int b[], char* text);
void draw_zxt(float lp[], Scalar cs);
void rect(Mat *img, Point sp, Point ep, Scalar co);
void line(Mat *img, Point sp, Point ep, Scalar co);

int _tmain(int argc, _TCHAR* argv[])
{
	CMycv mcv;
	Mat img = imread("src/test1.jpg", -1);
	Mat img2 = imread("src/MED.tif", -1);
	
	//获取直方图
	//Mat hist = mcv.RGB_Histogram(&img, 256, 256);
	//imshow("直方图", hist);

	//获取均衡化后的直方图
	//Mat equa = mcv.RGB_Equalization(&img);
	//imshow("直方图均衡化", equa);
	
	//RGB转单通道
	Mat grayimg = mcv.RGB_Gray(&img, 1);
	//imshow("rgb2gray", grayimg);

	//单通道直方图
	//Mat grayhist = mcv.Histogram(&grayimg, 256, 256);
	//imshow("单通道直方图", grayhist);

	//单通道直方图均衡
	//Mat grayequa = mcv.Equalization(&grayimg);
	//imshow("单通道直方图均衡化", grayequa);
	

	//线性模糊
	Mat FilterBlurLine1 = mcv.Filter_Blur_Line(&grayimg,3);
	Mat FilterBlurLine2 = mcv.Filter_Blur_Line(&grayimg,5);
	imshow("线性模糊3*3", FilterBlurLine1);
	imshow("线性模糊5*5", FilterBlurLine2);
	
	//中值滤波
	Mat FilterMedian = mcv.Filter_Median(&img2, 3);
	imshow("中值滤波", FilterMedian);

	imshow("img", img);
	imshow("img2", img2);
	waitKey();
	return 0;
}