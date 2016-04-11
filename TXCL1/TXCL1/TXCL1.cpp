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
	
	//��ȡֱ��ͼ
	//Mat hist = mcv.RGB_Histogram(&img, 256, 256);
	//imshow("ֱ��ͼ", hist);

	//��ȡ���⻯���ֱ��ͼ
	//Mat equa = mcv.RGB_Equalization(&img);
	//imshow("ֱ��ͼ���⻯", equa);
	
	//RGBת��ͨ��
	Mat grayimg = mcv.RGB_Gray(&img, 1);
	//imshow("rgb2gray", grayimg);

	//��ͨ��ֱ��ͼ
	//Mat grayhist = mcv.Histogram(&grayimg, 256, 256);
	//imshow("��ͨ��ֱ��ͼ", grayhist);

	//��ͨ��ֱ��ͼ����
	//Mat grayequa = mcv.Equalization(&grayimg);
	//imshow("��ͨ��ֱ��ͼ���⻯", grayequa);
	

	//����ģ��
	Mat FilterBlurLine1 = mcv.Filter_Blur_Line(&grayimg,3);
	Mat FilterBlurLine2 = mcv.Filter_Blur_Line(&grayimg,5);
	imshow("����ģ��3*3", FilterBlurLine1);
	imshow("����ģ��5*5", FilterBlurLine2);
	
	//��ֵ�˲�
	Mat FilterMedian = mcv.Filter_Median(&img2, 3);
	imshow("��ֵ�˲�", FilterMedian);

	imshow("img", img);
	imshow("img2", img2);
	waitKey();
	return 0;
}