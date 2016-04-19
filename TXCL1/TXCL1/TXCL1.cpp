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
	Mat moon = imread("src/moon.tif", -1);
	
	//获取直方图
	//Mat hist = mcv.RGB_Histogram(&img, 256, 256);
	//imshow("直方图", hist);

	//获取均衡化后的直方图
	//Mat equa = mcv.RGB_Equalization(&img);
	//imshow("直方图均衡化", equa);
	
	//RGB转单通道
	//Mat grayimg = mcv.RGB_Gray(&img, 1);
	//imshow("rgb2gray", grayimg);

	//单通道直方图
	//Mat grayhist = mcv.Histogram(&grayimg, 256, 256);
	//imshow("单通道直方图", grayhist);

	//单通道直方图均衡
	//Mat grayequa = mcv.Equalization(&grayimg);
	//imshow("单通道直方图均衡化", grayequa);
	

	//线性模糊
	//Mat FilterBlurLine1 = mcv.Filter_Blur_Line(&grayimg,3,3);
	//Mat FilterBlurLine2 = mcv.Filter_Blur_Line(&grayimg,7,7);
	//imshow("线性模糊3*3", FilterBlurLine1);
	//imshow("线性模糊7*7", FilterBlurLine2);
	
	//中值滤波
	//Mat FilterMedian = mcv.Filter_Median(&img2, 3);
	//imshow("中值滤波", FilterMedian);

	//拉布拉斯算子
	//Mat Laplasse1 = mcv.Filter_Laplasse_operator(&moon, 1);
	//Mat Laplasse2 = mcv.Filter_Laplasse_operator(&moon, 2);
	//Mat Laplasse3 = mcv.Filter_Laplasse_operator(&moon, 3);
	//Mat Laplasse4 = mcv.Filter_Laplasse_operator(&moon, 4);
	//imshow("拉布拉斯算子1", Laplasse1);
	//imshow("拉布拉斯算子2", Laplasse2);
	//imshow("拉布拉斯算子3", Laplasse3);
	//imshow("拉布拉斯算子4", Laplasse4);

	//DFT
	Mat dfttest = imread("src/滤波测试用例.tif", -1);
	Mat dft = mcv.DFT(dfttest);
	Mat dft_amplitudespectrum = mcv.DFT_AmplitudeSpectrum(dft);
	imshow("幅度谱", dft_amplitudespectrum);
	Mat dft_phasespectrum=mcv.DFT_PhaseSpectrum(dft);
	imshow("相位谱", dft_phasespectrum);
	Mat dft_realpart = mcv.DFT_RealPart(dft,true);
	imshow("实部谱", dft_realpart);
	Mat dft_imaginarypart = mcv.DFT_ImaginaryPart(dft,false);
	imshow("虚部谱", dft_imaginarypart);
	Mat idft=mcv.IDFT(dft, dfttest.rows, dfttest.cols);
	imshow("IDFT", idft);


	////////////////////    理想低通滤波    ////////////////////
	/*Mat ilpftest = imread("src/滤波测试用例.tif", -1);
	Mat dft_ilpf = mcv.DFT(ilpftest);
	Mat filt_10 = mcv.DFT_ILPF(dft_ilpf.rows, dft_ilpf.cols, 10);mcv.DFT_Filter_Show(filt_10, "filt_10");
	Mat filt_30 = mcv.DFT_ILPF(dft_ilpf.rows, dft_ilpf.cols, 30);mcv.DFT_Filter_Show(filt_30, "filt_30");
	Mat filt_60 = mcv.DFT_ILPF(dft_ilpf.rows, dft_ilpf.cols, 60);mcv.DFT_Filter_Show(filt_60, "filt_60");
	Mat filt_160 = mcv.DFT_ILPF(dft_ilpf.rows, dft_ilpf.cols, 160);mcv.DFT_Filter_Show(filt_160, "filt_160");
	Mat filt_460 = mcv.DFT_ILPF(dft_ilpf.rows, dft_ilpf.cols, 460);mcv.DFT_Filter_Show(filt_460, "filt_460");
	Mat dft_ilpf_10 = mcv.DFT_Filter(dft_ilpf, filt_10);
	Mat dft_ilpf_30 = mcv.DFT_Filter(dft_ilpf, filt_30);
	Mat dft_ilpf_60 = mcv.DFT_Filter(dft_ilpf, filt_60);
	Mat dft_ilpf_160 = mcv.DFT_Filter(dft_ilpf, filt_160);
	Mat dft_ilpf_460 = mcv.DFT_Filter(dft_ilpf, filt_460);
	Mat idft_ilpf_10 = mcv.IDFT(dft_ilpf_10, ilpftest.rows, ilpftest.cols);
	Mat idft_ilpf_30 = mcv.IDFT(dft_ilpf_30, ilpftest.rows, ilpftest.cols);
	Mat idft_ilpf_60 = mcv.IDFT(dft_ilpf_60, ilpftest.rows, ilpftest.cols);
	Mat idft_ilpf_160 = mcv.IDFT(dft_ilpf_160, ilpftest.rows, ilpftest.cols);
	Mat idft_ilpf_460 = mcv.IDFT(dft_ilpf_460, ilpftest.rows, ilpftest.cols);
	imshow("理想低通滤波器 d=10", idft_ilpf_10);
	imshow("理想低通滤波器 d=30", idft_ilpf_30);
	imshow("理想低通滤波器 d=60", idft_ilpf_60);
	imshow("理想低通滤波器 d=160", idft_ilpf_160);
	imshow("理想低通滤波器 d=460", idft_ilpf_460);
	imshow("理想低通滤波测试用例", ilpftest);*/


	////////////////////    布特沃斯低通滤波    ////////////////////
	/*Mat ilpftest = imread("src/滤波测试用例.tif", -1);
	Mat dft_ilpf = mcv.DFT(ilpftest);
	Mat filt_10 = mcv.DFT_BLPF(dft_ilpf.rows, dft_ilpf.cols, 10, 2); mcv.DFT_Filter_Show(filt_10, "filt_10");
	Mat filt_30 = mcv.DFT_BLPF(dft_ilpf.rows, dft_ilpf.cols, 30, 2); mcv.DFT_Filter_Show(filt_30, "filt_30");
	Mat filt_60 = mcv.DFT_BLPF(dft_ilpf.rows, dft_ilpf.cols, 60, 2); mcv.DFT_Filter_Show(filt_60, "filt_60");
	Mat filt_160 = mcv.DFT_BLPF(dft_ilpf.rows, dft_ilpf.cols, 160, 2); mcv.DFT_Filter_Show(filt_160, "filt_160");
	Mat filt_460 = mcv.DFT_BLPF(dft_ilpf.rows, dft_ilpf.cols, 460, 2); mcv.DFT_Filter_Show(filt_460, "filt_460");
	Mat dft_ilpf_10 = mcv.DFT_Filter(dft_ilpf, filt_10);
	Mat dft_ilpf_30 = mcv.DFT_Filter(dft_ilpf, filt_30);
	Mat dft_ilpf_60 = mcv.DFT_Filter(dft_ilpf, filt_60);
	Mat dft_ilpf_160 = mcv.DFT_Filter(dft_ilpf, filt_160);
	Mat dft_ilpf_460 = mcv.DFT_Filter(dft_ilpf, filt_460);
	Mat idft_ilpf_10 = mcv.IDFT(dft_ilpf_10, ilpftest.rows, ilpftest.cols);
	Mat idft_ilpf_30 = mcv.IDFT(dft_ilpf_30, ilpftest.rows, ilpftest.cols);
	Mat idft_ilpf_60 = mcv.IDFT(dft_ilpf_60, ilpftest.rows, ilpftest.cols);
	Mat idft_ilpf_160 = mcv.IDFT(dft_ilpf_160, ilpftest.rows, ilpftest.cols);
	Mat idft_ilpf_460 = mcv.IDFT(dft_ilpf_460, ilpftest.rows, ilpftest.cols);
	imshow("布特沃斯低通滤波器 d=10 n=2", idft_ilpf_10);
	imshow("布特沃斯低通滤波器 d=30 n=2", idft_ilpf_30);
	imshow("布特沃斯低通滤波器 d=60 n=2", idft_ilpf_60);
	imshow("布特沃斯低通滤波器 d=160 n=2", idft_ilpf_160);
	imshow("布特沃斯低通滤波器 d=460 n=2", idft_ilpf_460);
	imshow("布特沃斯低通滤波测试用例", ilpftest);*/
	

	////////////////////    高斯低通滤波    ////////////////////
	/*Mat ilpftest = imread("src/滤波测试用例.tif", -1);
	Mat dft_ilpf = mcv.DFT(ilpftest);
	Mat filt_10 = mcv.DFT_GLPF(dft_ilpf.rows, dft_ilpf.cols, 10); mcv.DFT_Filter_Show(filt_10, "filt_10");
	Mat filt_30 = mcv.DFT_GLPF(dft_ilpf.rows, dft_ilpf.cols, 30); mcv.DFT_Filter_Show(filt_30, "filt_30");
	Mat filt_60 = mcv.DFT_GLPF(dft_ilpf.rows, dft_ilpf.cols, 60); mcv.DFT_Filter_Show(filt_60, "filt_60");
	Mat filt_160 = mcv.DFT_GLPF(dft_ilpf.rows, dft_ilpf.cols, 160); mcv.DFT_Filter_Show(filt_160, "filt_160");
	Mat filt_460 = mcv.DFT_GLPF(dft_ilpf.rows, dft_ilpf.cols, 460); mcv.DFT_Filter_Show(filt_460, "filt_460");
	Mat dft_ilpf_10 = mcv.DFT_Filter(dft_ilpf, filt_10);
	Mat dft_ilpf_30 = mcv.DFT_Filter(dft_ilpf, filt_30);
	Mat dft_ilpf_60 = mcv.DFT_Filter(dft_ilpf, filt_60);
	Mat dft_ilpf_160 = mcv.DFT_Filter(dft_ilpf, filt_160);
	Mat dft_ilpf_460 = mcv.DFT_Filter(dft_ilpf, filt_460);
	Mat idft_ilpf_10 = mcv.IDFT(dft_ilpf_10, ilpftest.rows, ilpftest.cols);
	Mat idft_ilpf_30 = mcv.IDFT(dft_ilpf_30, ilpftest.rows, ilpftest.cols);
	Mat idft_ilpf_60 = mcv.IDFT(dft_ilpf_60, ilpftest.rows, ilpftest.cols);
	Mat idft_ilpf_160 = mcv.IDFT(dft_ilpf_160, ilpftest.rows, ilpftest.cols);
	Mat idft_ilpf_460 = mcv.IDFT(dft_ilpf_460, ilpftest.rows, ilpftest.cols);
	imshow("高斯低通滤波器 d=10", idft_ilpf_10);
	imshow("高斯低通滤波器 d=30", idft_ilpf_30);
	imshow("高斯低通滤波器 d=60", idft_ilpf_60);
	imshow("高斯低通滤波器 d=160", idft_ilpf_160);
	imshow("高斯低通滤波器 d=460", idft_ilpf_460);
	imshow("高斯低通滤波测试用例", ilpftest);*/


	////////////////////    理想高通滤波    ////////////////////
	/*Mat ilpftest = imread("src/滤波测试用例.tif", -1);
	Mat dft_ilpf = mcv.DFT(ilpftest);
	Mat filt_30 = mcv.DFT_IHPF(dft_ilpf.rows, dft_ilpf.cols, 30); mcv.DFT_Filter_Show(filt_30, "filt_30");
	Mat filt_60 = mcv.DFT_IHPF(dft_ilpf.rows, dft_ilpf.cols, 60); mcv.DFT_Filter_Show(filt_60, "filt_60");
	Mat filt_160 = mcv.DFT_IHPF(dft_ilpf.rows, dft_ilpf.cols, 160); mcv.DFT_Filter_Show(filt_160, "filt_160");
	Mat dft_ilpf_30 = mcv.DFT_Filter(dft_ilpf, filt_30);
	Mat dft_ilpf_60 = mcv.DFT_Filter(dft_ilpf, filt_60);
	Mat dft_ilpf_160 = mcv.DFT_Filter(dft_ilpf, filt_160);
	Mat idft_ilpf_30 = mcv.IDFT(dft_ilpf_30, ilpftest.rows, ilpftest.cols);
	Mat idft_ilpf_60 = mcv.IDFT(dft_ilpf_60, ilpftest.rows, ilpftest.cols);
	Mat idft_ilpf_160 = mcv.IDFT(dft_ilpf_160, ilpftest.rows, ilpftest.cols);
	imshow("理想高通滤波器 d=30", idft_ilpf_30);
	imshow("理想高通滤波器 d=60", idft_ilpf_60);
	imshow("理想高通滤波器 d=160", idft_ilpf_160);
	imshow("理想高通滤波测试用例", ilpftest);*/


	//////////////////////    布特沃斯高通滤波    ////////////////////
	//Mat ilpftest = imread("src/滤波测试用例.tif", -1);
	//Mat dft_ilpf = mcv.DFT(ilpftest);
	//Mat filt_30 = mcv.DFT_BHPF(dft_ilpf.rows, dft_ilpf.cols, 30,2); mcv.DFT_Filter_Show(filt_30, "filt_30");
	//Mat filt_60 = mcv.DFT_BHPF(dft_ilpf.rows, dft_ilpf.cols, 60,2); mcv.DFT_Filter_Show(filt_60, "filt_60");
	//Mat filt_160 = mcv.DFT_BHPF(dft_ilpf.rows, dft_ilpf.cols, 160,2); mcv.DFT_Filter_Show(filt_160, "filt_160");
	//Mat dft_ilpf_30 = mcv.DFT_Filter(dft_ilpf, filt_30);
	//Mat dft_ilpf_60 = mcv.DFT_Filter(dft_ilpf, filt_60);
	//Mat dft_ilpf_160 = mcv.DFT_Filter(dft_ilpf, filt_160);
	//Mat idft_ilpf_30 = mcv.IDFT(dft_ilpf_30, ilpftest.rows, ilpftest.cols);
	//Mat idft_ilpf_60 = mcv.IDFT(dft_ilpf_60, ilpftest.rows, ilpftest.cols);
	//Mat idft_ilpf_160 = mcv.IDFT(dft_ilpf_160, ilpftest.rows, ilpftest.cols);
	//imshow("布特沃斯高通滤波器 d=30 n=2", idft_ilpf_30);
	//imshow("布特沃斯高通滤波器 d=60 n=2", idft_ilpf_60);
	//imshow("布特沃斯高通滤波器 d=160 n=2", idft_ilpf_160);
	//imshow("布特沃斯高通滤波测试用例", ilpftest);


	////////////////////    高斯高通滤波    ////////////////////
	/*Mat ilpftest = imread("src/滤波测试用例.tif", -1);
	Mat dft_ilpf = mcv.DFT(ilpftest);
	Mat filt_30 = mcv.DFT_GHPF(dft_ilpf.rows, dft_ilpf.cols, 30); mcv.DFT_Filter_Show(filt_30, "filt_30");
	Mat filt_60 = mcv.DFT_GHPF(dft_ilpf.rows, dft_ilpf.cols, 60); mcv.DFT_Filter_Show(filt_60, "filt_60");
	Mat filt_160 = mcv.DFT_GHPF(dft_ilpf.rows, dft_ilpf.cols, 160); mcv.DFT_Filter_Show(filt_160, "filt_160");
	Mat dft_ilpf_30 = mcv. DFT_Filter(dft_ilpf, filt_30);
	Mat dft_ilpf_60 = mcv.DFT_Filter(dft_ilpf, filt_60);
	Mat dft_ilpf_160 = mcv.DFT_Filter(dft_ilpf, filt_160);
	Mat idft_ilpf_30 = mcv.IDFT(dft_ilpf_30, ilpftest.rows, ilpftest.cols);
	Mat idft_ilpf_60 = mcv.IDFT(dft_ilpf_60, ilpftest.rows, ilpftest.cols);
	Mat idft_ilpf_160 = mcv.IDFT(dft_ilpf_160, ilpftest.rows, ilpftest.cols);
	imshow("高斯高通滤波器 d=30", idft_ilpf_30);
	imshow("高斯高通滤波器 d=60", idft_ilpf_60);
	imshow("高斯高通滤波器 d=160", idft_ilpf_160);
	imshow("高斯高通滤波测试用例", ilpftest);*/
	

	////////////////////    频率域拉普拉斯滤波    ////////////////////
	//Mat ilpftest = imread("src/moon.tif", -1);
	//Mat dft_lapls = mcv.DFT(ilpftest);
	//Mat filt = mcv.DFT_LAPLS(dft_lapls.rows, dft_lapls.cols); 
	//	mcv.DFT_Filter_Show(filt, "filt");
	//Mat filt_idft = mcv.IDFT(filt);
	//Mat idft_lapls = mcv.DFT_Filter(dft_lapls, filt);
	////imshow(" 频率域拉不拉斯滤波", idft_lapls);
	//imshow(" 频率域拉不拉斯滤波例子", ilpftest);


	waitKey();
	return 0;
}