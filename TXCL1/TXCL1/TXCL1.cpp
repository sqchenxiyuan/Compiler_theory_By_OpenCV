// TXCL1.cpp : �������̨Ӧ�ó������ڵ㡣
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
	
	//��ȡֱ��ͼ
	//Mat hist = mcv.RGB_Histogram(&img, 256, 256);
	//imshow("ֱ��ͼ", hist);

	//��ȡ���⻯���ֱ��ͼ
	//Mat equa = mcv.RGB_Equalization(&img);
	//imshow("ֱ��ͼ���⻯", equa);
	
	//RGBת��ͨ��
	//Mat grayimg = mcv.RGB_Gray(&img, 1);
	//imshow("rgb2gray", grayimg);

	//��ͨ��ֱ��ͼ
	//Mat grayhist = mcv.Histogram(&grayimg, 256, 256);
	//imshow("��ͨ��ֱ��ͼ", grayhist);

	//��ͨ��ֱ��ͼ����
	//Mat grayequa = mcv.Equalization(&grayimg);
	//imshow("��ͨ��ֱ��ͼ���⻯", grayequa);
	

	//����ģ��
	//Mat FilterBlurLine1 = mcv.Filter_Blur_Line(&grayimg,3,3);
	//Mat FilterBlurLine2 = mcv.Filter_Blur_Line(&grayimg,7,7);
	//imshow("����ģ��3*3", FilterBlurLine1);
	//imshow("����ģ��7*7", FilterBlurLine2);
	
	//��ֵ�˲�
	//Mat FilterMedian = mcv.Filter_Median(&img2, 3);
	//imshow("��ֵ�˲�", FilterMedian);

	//������˹����
	//Mat Laplasse1 = mcv.Filter_Laplasse_operator(&moon, 1);
	//Mat Laplasse2 = mcv.Filter_Laplasse_operator(&moon, 2);
	//Mat Laplasse3 = mcv.Filter_Laplasse_operator(&moon, 3);
	//Mat Laplasse4 = mcv.Filter_Laplasse_operator(&moon, 4);
	//imshow("������˹����1", Laplasse1);
	//imshow("������˹����2", Laplasse2);
	//imshow("������˹����3", Laplasse3);
	//imshow("������˹����4", Laplasse4);

	//DFT
	Mat dfttest = imread("src/�˲���������.tif", -1);
	Mat dft = mcv.DFT(dfttest);
	Mat dft_amplitudespectrum = mcv.DFT_AmplitudeSpectrum(dft);
	imshow("������", dft_amplitudespectrum);
	Mat dft_phasespectrum=mcv.DFT_PhaseSpectrum(dft);
	imshow("��λ��", dft_phasespectrum);
	Mat dft_realpart = mcv.DFT_RealPart(dft,true);
	imshow("ʵ����", dft_realpart);
	Mat dft_imaginarypart = mcv.DFT_ImaginaryPart(dft,false);
	imshow("�鲿��", dft_imaginarypart);
	Mat idft=mcv.IDFT(dft, dfttest.rows, dfttest.cols);
	imshow("IDFT", idft);


	////////////////////    �����ͨ�˲�    ////////////////////
	/*Mat ilpftest = imread("src/�˲���������.tif", -1);
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
	imshow("�����ͨ�˲��� d=10", idft_ilpf_10);
	imshow("�����ͨ�˲��� d=30", idft_ilpf_30);
	imshow("�����ͨ�˲��� d=60", idft_ilpf_60);
	imshow("�����ͨ�˲��� d=160", idft_ilpf_160);
	imshow("�����ͨ�˲��� d=460", idft_ilpf_460);
	imshow("�����ͨ�˲���������", ilpftest);*/


	////////////////////    ������˹��ͨ�˲�    ////////////////////
	/*Mat ilpftest = imread("src/�˲���������.tif", -1);
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
	imshow("������˹��ͨ�˲��� d=10 n=2", idft_ilpf_10);
	imshow("������˹��ͨ�˲��� d=30 n=2", idft_ilpf_30);
	imshow("������˹��ͨ�˲��� d=60 n=2", idft_ilpf_60);
	imshow("������˹��ͨ�˲��� d=160 n=2", idft_ilpf_160);
	imshow("������˹��ͨ�˲��� d=460 n=2", idft_ilpf_460);
	imshow("������˹��ͨ�˲���������", ilpftest);*/
	

	////////////////////    ��˹��ͨ�˲�    ////////////////////
	/*Mat ilpftest = imread("src/�˲���������.tif", -1);
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
	imshow("��˹��ͨ�˲��� d=10", idft_ilpf_10);
	imshow("��˹��ͨ�˲��� d=30", idft_ilpf_30);
	imshow("��˹��ͨ�˲��� d=60", idft_ilpf_60);
	imshow("��˹��ͨ�˲��� d=160", idft_ilpf_160);
	imshow("��˹��ͨ�˲��� d=460", idft_ilpf_460);
	imshow("��˹��ͨ�˲���������", ilpftest);*/


	////////////////////    �����ͨ�˲�    ////////////////////
	/*Mat ilpftest = imread("src/�˲���������.tif", -1);
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
	imshow("�����ͨ�˲��� d=30", idft_ilpf_30);
	imshow("�����ͨ�˲��� d=60", idft_ilpf_60);
	imshow("�����ͨ�˲��� d=160", idft_ilpf_160);
	imshow("�����ͨ�˲���������", ilpftest);*/


	//////////////////////    ������˹��ͨ�˲�    ////////////////////
	//Mat ilpftest = imread("src/�˲���������.tif", -1);
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
	//imshow("������˹��ͨ�˲��� d=30 n=2", idft_ilpf_30);
	//imshow("������˹��ͨ�˲��� d=60 n=2", idft_ilpf_60);
	//imshow("������˹��ͨ�˲��� d=160 n=2", idft_ilpf_160);
	//imshow("������˹��ͨ�˲���������", ilpftest);


	////////////////////    ��˹��ͨ�˲�    ////////////////////
	/*Mat ilpftest = imread("src/�˲���������.tif", -1);
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
	imshow("��˹��ͨ�˲��� d=30", idft_ilpf_30);
	imshow("��˹��ͨ�˲��� d=60", idft_ilpf_60);
	imshow("��˹��ͨ�˲��� d=160", idft_ilpf_160);
	imshow("��˹��ͨ�˲���������", ilpftest);*/
	

	////////////////////    Ƶ����������˹�˲�    ////////////////////
	//Mat ilpftest = imread("src/moon.tif", -1);
	//Mat dft_lapls = mcv.DFT(ilpftest);
	//Mat filt = mcv.DFT_LAPLS(dft_lapls.rows, dft_lapls.cols); 
	//	mcv.DFT_Filter_Show(filt, "filt");
	//Mat filt_idft = mcv.IDFT(filt);
	//Mat idft_lapls = mcv.DFT_Filter(dft_lapls, filt);
	////imshow(" Ƶ����������˹�˲�", idft_lapls);
	//imshow(" Ƶ����������˹�˲�����", ilpftest);


	waitKey();
	return 0;
}