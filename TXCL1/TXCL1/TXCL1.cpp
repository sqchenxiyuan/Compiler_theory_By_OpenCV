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
	Mat dfttest = imread("src/DFTtest1.tif", -1);
	
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
	Mat dft = mcv.DFT(dfttest);
	Mat dft_amplitudespectrum = mcv.DFT_AmplitudeSpectrum(dft);
	imshow("������", dft_amplitudespectrum);
	Mat dft_phasespectrum=mcv.DFT_PhaseSpectrum(dft);
	imshow("��λ��", dft_phasespectrum);
	Mat dft_realpart = mcv.DFT_RealPart(dft,true);
	imshow("ʵ����", dft_realpart);
	Mat dft_imaginarypart = mcv.DFT_ImaginaryPart(dft,false);
	imshow("�鲿��", dft_imaginarypart);
	Mat idft = mcv.IDFT(dft,dfttest.rows,dfttest.cols);
	imshow("idft", idft);


	//imshow("img", img);
	//imshow("img2", img2);
	//imshow("moon", moon);
	waitKey();
	return 0;
}