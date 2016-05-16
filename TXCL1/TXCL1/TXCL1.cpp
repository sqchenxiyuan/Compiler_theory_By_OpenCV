// TXCL1.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"

int _tmain(int argc, _TCHAR* argv[])
{
	CMycv mcv;
	
	//Mat img = imread("src/test1.jpg", -1);
	////获取直方图
	//Mat hist = mcv.RGB_Histogram(&img, 256, 256);
	//imshow("直方图", hist);
	////获取均衡化后的直方图
	//Mat equa = mcv.RGB_Equalization(&img);
	//imshow("直方图均衡化", equa);
	////RGB转单通道
	//Mat grayimg = mcv.RGB_Gray(&img, 1);
	//imshow("rgb2gray", grayimg);
	////单通道直方图
	//Mat grayhist = mcv.Histogram(&grayimg, 256, 256);
	//imshow("单通道直方图", grayhist);
	////单通道直方图均衡
	//Mat grayequa = mcv.Equalization(&grayimg);
	//imshow("单通道直方图均衡化", grayequa);
	//imshow("原图", img);


	//线性模糊
	/*Mat motest = imread("src/模糊测试用例.tif", -1);
	cout << "请稍等=。=" << endl;
	Mat FilterBlurLine1 = mcv.Filter_Blur_Line(&motest, 3, 3);
	Mat FilterBlurLine2 = mcv.Filter_Blur_Line(&motest, 7, 7);
	imshow("线性模糊3*3", FilterBlurLine1);
	imshow("线性模糊7*7", FilterBlurLine2);
	imshow("模糊测试用例", motest);*/
	
	//中值滤波
	/*Mat med = imread("src/中值滤波测试用例.tif", -1);
	cout << "请稍等=。=" << endl;
	Mat FilterMedian = mcv.Filter_Median(&med, 5);
	imshow("中值滤波测试用例", med);
	imshow("中值滤波结果", FilterMedian);*/

	//拉布拉斯算子
	/*Mat lapltest_k = imread("src/拉普拉斯测试用例.tif", -1);
	Mat Laplasse1 = mcv.Filter_Laplasse_operator(&lapltest_k, 1);
	Mat Laplasse2 = mcv.Filter_Laplasse_operator(&lapltest_k, 2);
	Mat Laplasse3 = mcv.Filter_Laplasse_operator(&lapltest_k, 3);
	Mat Laplasse4 = mcv.Filter_Laplasse_operator(&lapltest_k, 4);
	imshow("拉布拉斯算子1-完全", Laplasse1);
	imshow("拉布拉斯算子2-完全", Laplasse2);
	imshow("拉布拉斯算子3-轮廓", Laplasse3);
	imshow("拉布拉斯算子4-轮廓", Laplasse4);
	imshow("拉普拉斯测试用例", lapltest_k);*/

	//DFT
	/*Mat dfttest = imread("src/DFT_IDFT测试用例.tif", -1);
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
	imshow("IDFT", idft);*/


	////////////////////    理想低通滤波    ////////////////////
	/*Mat ilpftest = imread("src/滤波测试用例.tif", -1);
	imshow("理想低通滤波器 d=10", mcv.DFT_ILPF(ilpftest,10));
	imshow("理想低通滤波器 d=30", mcv.DFT_ILPF(ilpftest, 30));
	imshow("理想低通滤波器 d=60", mcv.DFT_ILPF(ilpftest, 60));
	imshow("理想低通滤波器 d=160", mcv.DFT_ILPF(ilpftest, 160));
	imshow("理想低通滤波器 d=460", mcv.DFT_ILPF(ilpftest, 460));
	imshow("理想低通滤波测试用例", ilpftest);*/


	////////////////////    布特沃斯低通滤波    ////////////////////
	/*Mat blpftest = imread("src/滤波测试用例.tif", -1);
	imshow("布特沃斯低通滤波器 d=10 n=2", mcv.DFT_BLPF(blpftest,10,2));
	imshow("布特沃斯低通滤波器 d=30 n=2", mcv.DFT_BLPF(blpftest, 30, 2));
	imshow("布特沃斯低通滤波器 d=60 n=2", mcv.DFT_BLPF(blpftest, 60, 2));
	imshow("布特沃斯低通滤波器 d=160 n=2", mcv.DFT_BLPF(blpftest, 160, 2));
	imshow("布特沃斯低通滤波器 d=460 n=2", mcv.DFT_BLPF(blpftest, 460, 2));
	imshow("布特沃斯低通滤波测试用例", blpftest);*/
	

	////////////////////    高斯低通滤波    ////////////////////
	/*Mat glpftest = imread("src/滤波测试用例.tif", -1);
	imshow("高斯低通滤波器 d=10", mcv.DFT_GLPF(glpftest,10));
	imshow("高斯低通滤波器 d=30", mcv.DFT_GLPF(glpftest, 30));
	imshow("高斯低通滤波器 d=60", mcv.DFT_GLPF(glpftest, 60));
	imshow("高斯低通滤波器 d=160", mcv.DFT_GLPF(glpftest, 160));
	imshow("高斯低通滤波器 d=460", mcv.DFT_GLPF(glpftest, 460));
	imshow("高斯低通滤波测试用例", glpftest);*/


	////////////////////    理想高通滤波    ////////////////////
	/*Mat ihpftest = imread("src/滤波测试用例.tif", -1);
	imshow("理想高通滤波器 d=30", mcv.DFT_IHPF(ihpftest,30));
	imshow("理想高通滤波器 d=60", mcv.DFT_IHPF(ihpftest, 60));
	imshow("理想高通滤波器 d=160", mcv.DFT_IHPF(ihpftest, 160));
	imshow("理想高通滤波测试用例", ihpftest);*/


	//////////////////////    布特沃斯高通滤波    ////////////////////
	/*Mat bhpftest = imread("src/滤波测试用例.tif", -1);
	imshow("布特沃斯高通滤波器 d=30 n=2", mcv.DFT_BHPF(bhpftest,30,2));
	imshow("布特沃斯高通滤波器 d=60 n=2", mcv.DFT_BHPF(bhpftest, 60, 2));
	imshow("布特沃斯高通滤波器 d=160 n=2", mcv.DFT_BHPF(bhpftest, 160, 2));
	imshow("布特沃斯高通滤波测试用例", bhpftest);*/


	////////////////////    高斯高通滤波    ////////////////////
	/*Mat ghpftest = imread("src/滤波测试用例.tif", -1);
	imshow("高斯高通滤波器 d=30", mcv.DFT_GHPF(ghpftest,30));
	imshow("高斯高通滤波器 d=60", mcv.DFT_GHPF(ghpftest, 60));
	imshow("高斯高通滤波器 d=160", mcv.DFT_GHPF(ghpftest, 160));
	imshow("高斯高通滤波测试用例", ghpftest);*/
	

	////////////////////    频率域拉普拉斯滤波    ////////////////////
	/*Mat lapltest_p = imread("src/拉普拉斯测试用例.tif", -1);
	Mat lapl = mcv.DFT_LAPLS(lapltest_p);
	imshow("频率域拉普拉斯", lapl);
	imshow("拉普拉斯测试用例", lapltest_p);*/



	/////////////////////    图像复原 逆滤波    /////////////////////

	//Mat motest = mcv.RGB_Gray(& imread("src/test1.jpg",-1),1);
	//int x[] = {1,1,1,1,1,1,1,
	//	1, 1, 1, 1, 1, 1, 1,
	//	1, 1, 1, 1, 1, 1, 1,
	//	1, 1, 1, 1, 1, 1, 1,
	//	1, 1, 1, 1, 1, 1, 1,
	//	1, 1, 1, 1, 1, 1, 1, 
	//	1, 1, 1, 1, 1, 1, 1, };//测试用滤波
	//CFilteringMask mask(7, 7, 1.0 / 49, x);
	//Mat moimg = mask.ALLProcess(&motest);
	//moimg = mcv.Matuchar2float(moimg);//空间域模糊后图像
	////空间域转频率域
	//Mat flt(7, 7, CV_8U, Scalar(1.0 / 49 * 255));

	//Mat bflt;
	//copyMakeBorder(flt, bflt, 0, motest.rows - flt.rows, 0, motest.cols - flt.cols, BORDER_CONSTANT, Scalar::all(0));
	//Mat fltdft = mcv.DFT(bflt);
	//Mat modft = mcv.DFT(moimg);

	//Mat planes[2];
	//split(fltdft, planes);


	//imshow("原图像", motest);
	//imshow("模糊后图像", moimg);


	///////////////////////////////展示用
	//Mat mo_Wiener= mcv.DFT_Inverse_Wiener(modft, fltdft, 10);
	//imshow("原图直方图", mcv.Histogram(&motest, 256, 1024));
	//Mat zimg = mcv.IDFT(mo_Wiener, motest.rows, motest.cols, -2.2, 3);
	//imshow("直方图用于矫正颜色", mcv.Histogram(&zimg, 256, 1024));
	//imshow("校正后逆滤波成果", zimg);



	////////////////////    维纳滤波    ////////////////////
	/*Mat mo_Wiener_0 = mcv.DFT_Inverse_Wiener(modft, fltdft, 0);
	Mat mo_Wiener_1 = mcv.DFT_Inverse_Wiener(modft, fltdft, 1);
	Mat mo_Wiener_10 = mcv.DFT_Inverse_Wiener(modft, fltdft, 10);
	Mat mo_Wiener_100 = mcv.DFT_Inverse_Wiener(modft, fltdft, 100);
	Mat mo_Wiener_1000 = mcv.DFT_Inverse_Wiener(modft, fltdft, 1000);
	Mat mo_Wiener_10000 = mcv.DFT_Inverse_Wiener(modft, fltdft, 10000);
	Mat mo_Wiener_50000 = mcv.DFT_Inverse_Wiener(modft, fltdft, 50000);
	Mat mo_Wiener_100000 = mcv.DFT_Inverse_Wiener(modft, fltdft, 100000);
	
	imshow("维纳滤波 k=0", mcv.IDFT(mo_Wiener_0, motest.rows, motest.cols, 0));
	imshow("维纳滤波 k=1", mcv.IDFT(mo_Wiener_1, motest.rows, motest.cols, 0));
	imshow("维纳滤波 k=10", mcv.IDFT(mo_Wiener_10, motest.rows, motest.cols, 0));
	imshow("维纳滤波 k=100",  mcv.IDFT(mo_Wiener_100, motest.rows, motest.cols,0));
	imshow("维纳滤波 k=1000", mcv.IDFT(mo_Wiener_1000, motest.rows, motest.cols, 0));
	imshow("维纳滤波 k=100000", mcv.IDFT(mo_Wiener_10000, motest.rows, motest.cols,0));
	imshow("维纳滤波 k=500000", mcv.IDFT(mo_Wiener_50000, motest.rows, motest.cols,0));
	imshow("维纳滤波 k=1000000", mcv.IDFT(mo_Wiener_100000, motest.rows, motest.cols,0));*/

	////////////////////    约束最小二乘方滤波   ////////////////////
	///*Mat mo_ICLSF_0 = mcv.DFT_Inverse_Constrained_Least_Squares_Filtering(modft, fltdft, 0);
	//Mat mo_ICLSF_01 = mcv.DFT_Inverse_Constrained_Least_Squares_Filtering(modft, fltdft, 0.1);
	//Mat mo_ICLSF_00001 = mcv.DFT_Inverse_Constrained_Least_Squares_Filtering(modft, fltdft, 0.0001);
	//Mat mo_ICLSF_0000001 = mcv.DFT_Inverse_Constrained_Least_Squares_Filtering(modft, fltdft, 0.000001);
	//Mat mo_ICLSF_0000000001 = mcv.DFT_Inverse_Constrained_Least_Squares_Filtering(modft, fltdft, 0.000000001);

	//imshow("约束最小二乘方滤波 l=0.0", mcv.IDFT(mo_ICLSF_0, motest.rows, motest.cols, 0));
	//imshow("约束最小二乘方滤波 l=0.1", mcv.IDFT(mo_ICLSF_01, motest.rows, motest.cols, 0));
	//imshow("约束最小二乘方滤波 l=0.0001", mcv.IDFT(mo_ICLSF_00001, motest.rows, motest.cols, 0));
	//imshow("约束最小二乘方滤波 l=0.000001", mcv.IDFT(mo_ICLSF_0000001, motest.rows, motest.cols, 0));
	//imshow("约束最小二乘方滤波 l=0.000000001", mcv.IDFT(mo_ICLSF_0000000001, motest.rows, motest.cols, 0));*/





	/////////////////////    边缘检测   瞳孔检测   /////////////////////

	//mcv.Huo_Fuyuan_transform();
	mcv.HoughLine();
	

	waitKey();
	return 0;
}