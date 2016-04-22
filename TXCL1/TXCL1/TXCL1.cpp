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
	
	//Mat img = imread("src/test1.jpg", -1);
	////��ȡֱ��ͼ
	//Mat hist = mcv.RGB_Histogram(&img, 256, 256);
	//imshow("ֱ��ͼ", hist);
	////��ȡ���⻯���ֱ��ͼ
	//Mat equa = mcv.RGB_Equalization(&img);
	//imshow("ֱ��ͼ���⻯", equa);
	////RGBת��ͨ��
	//Mat grayimg = mcv.RGB_Gray(&img, 1);
	//imshow("rgb2gray", grayimg);
	////��ͨ��ֱ��ͼ
	//Mat grayhist = mcv.Histogram(&grayimg, 256, 256);
	//imshow("��ͨ��ֱ��ͼ", grayhist);
	////��ͨ��ֱ��ͼ����
	//Mat grayequa = mcv.Equalization(&grayimg);
	//imshow("��ͨ��ֱ��ͼ���⻯", grayequa);
	//imshow("ԭͼ", img);


	//����ģ��
	/*Mat motest = imread("src/ģ����������.tif", -1);
	cout << "���Ե�=��=" << endl;
	Mat FilterBlurLine1 = mcv.Filter_Blur_Line(&motest, 3, 3);
	Mat FilterBlurLine2 = mcv.Filter_Blur_Line(&motest, 7, 7);
	imshow("����ģ��3*3", FilterBlurLine1);
	imshow("����ģ��7*7", FilterBlurLine2);
	imshow("ģ����������", motest);*/
	
	//��ֵ�˲�
	/*Mat med = imread("src/��ֵ�˲���������.tif", -1);
	cout << "���Ե�=��=" << endl;
	Mat FilterMedian = mcv.Filter_Median(&med, 5);
	imshow("��ֵ�˲���������", med);
	imshow("��ֵ�˲����", FilterMedian);*/

	//������˹����
	/*Mat lapltest_k = imread("src/������˹��������.tif", -1);
	Mat Laplasse1 = mcv.Filter_Laplasse_operator(&lapltest_k, 1);
	Mat Laplasse2 = mcv.Filter_Laplasse_operator(&lapltest_k, 2);
	Mat Laplasse3 = mcv.Filter_Laplasse_operator(&lapltest_k, 3);
	Mat Laplasse4 = mcv.Filter_Laplasse_operator(&lapltest_k, 4);
	imshow("������˹����1-��ȫ", Laplasse1);
	imshow("������˹����2-��ȫ", Laplasse2);
	imshow("������˹����3-����", Laplasse3);
	imshow("������˹����4-����", Laplasse4);
	imshow("������˹��������", lapltest_k);*/

	//DFT
	/*Mat dfttest = imread("src/DFT_IDFT��������.tif", -1);
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
	imshow("IDFT", idft);*/


	////////////////////    �����ͨ�˲�    ////////////////////
	/*Mat ilpftest = imread("src/�˲���������.tif", -1);
	imshow("�����ͨ�˲��� d=10", mcv.DFT_ILPF(ilpftest,10));
	imshow("�����ͨ�˲��� d=30", mcv.DFT_ILPF(ilpftest, 30));
	imshow("�����ͨ�˲��� d=60", mcv.DFT_ILPF(ilpftest, 60));
	imshow("�����ͨ�˲��� d=160", mcv.DFT_ILPF(ilpftest, 160));
	imshow("�����ͨ�˲��� d=460", mcv.DFT_ILPF(ilpftest, 460));
	imshow("�����ͨ�˲���������", ilpftest);*/


	////////////////////    ������˹��ͨ�˲�    ////////////////////
	/*Mat blpftest = imread("src/�˲���������.tif", -1);
	imshow("������˹��ͨ�˲��� d=10 n=2", mcv.DFT_BLPF(blpftest,10,2));
	imshow("������˹��ͨ�˲��� d=30 n=2", mcv.DFT_BLPF(blpftest, 30, 2));
	imshow("������˹��ͨ�˲��� d=60 n=2", mcv.DFT_BLPF(blpftest, 60, 2));
	imshow("������˹��ͨ�˲��� d=160 n=2", mcv.DFT_BLPF(blpftest, 160, 2));
	imshow("������˹��ͨ�˲��� d=460 n=2", mcv.DFT_BLPF(blpftest, 460, 2));
	imshow("������˹��ͨ�˲���������", blpftest);*/
	

	////////////////////    ��˹��ͨ�˲�    ////////////////////
	/*Mat glpftest = imread("src/�˲���������.tif", -1);
	imshow("��˹��ͨ�˲��� d=10", mcv.DFT_GLPF(glpftest,10));
	imshow("��˹��ͨ�˲��� d=30", mcv.DFT_GLPF(glpftest, 30));
	imshow("��˹��ͨ�˲��� d=60", mcv.DFT_GLPF(glpftest, 60));
	imshow("��˹��ͨ�˲��� d=160", mcv.DFT_GLPF(glpftest, 160));
	imshow("��˹��ͨ�˲��� d=460", mcv.DFT_GLPF(glpftest, 460));
	imshow("��˹��ͨ�˲���������", glpftest);*/


	////////////////////    �����ͨ�˲�    ////////////////////
	/*Mat ihpftest = imread("src/�˲���������.tif", -1);
	imshow("�����ͨ�˲��� d=30", mcv.DFT_IHPF(ihpftest,30));
	imshow("�����ͨ�˲��� d=60", mcv.DFT_IHPF(ihpftest, 60));
	imshow("�����ͨ�˲��� d=160", mcv.DFT_IHPF(ihpftest, 160));
	imshow("�����ͨ�˲���������", ihpftest);*/


	//////////////////////    ������˹��ͨ�˲�    ////////////////////
	/*Mat bhpftest = imread("src/�˲���������.tif", -1);
	imshow("������˹��ͨ�˲��� d=30 n=2", mcv.DFT_BHPF(bhpftest,30,2));
	imshow("������˹��ͨ�˲��� d=60 n=2", mcv.DFT_BHPF(bhpftest, 60, 2));
	imshow("������˹��ͨ�˲��� d=160 n=2", mcv.DFT_BHPF(bhpftest, 160, 2));
	imshow("������˹��ͨ�˲���������", bhpftest);*/


	////////////////////    ��˹��ͨ�˲�    ////////////////////
	/*Mat ghpftest = imread("src/�˲���������.tif", -1);
	imshow("��˹��ͨ�˲��� d=30", mcv.DFT_GHPF(ghpftest,30));
	imshow("��˹��ͨ�˲��� d=60", mcv.DFT_GHPF(ghpftest, 60));
	imshow("��˹��ͨ�˲��� d=160", mcv.DFT_GHPF(ghpftest, 160));
	imshow("��˹��ͨ�˲���������", ghpftest);*/
	

	////////////////////    Ƶ����������˹�˲�    ////////////////////
	/*Mat lapltest_p = imread("src/moon.tif", -1);
	Mat lapl = mcv.DFT_LAPLS(lapltest_p);
	imshow("Ƶ����������˹", lapl);
	imshow("������˹��������", lapltest_p);*/


	waitKey();
	return 0;
}