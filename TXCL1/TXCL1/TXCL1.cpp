// TXCL1.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"

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
	/*Mat lapltest_p = imread("src/������˹��������.tif", -1);
	Mat lapl = mcv.DFT_LAPLS(lapltest_p);
	imshow("Ƶ����������˹", lapl);
	imshow("������˹��������", lapltest_p);*/



	/////////////////////    ͼ��ԭ ���˲�    /////////////////////

	//Mat motest = mcv.RGB_Gray(& imread("src/test1.jpg",-1),1);
	//int x[] = {1,1,1,1,1,1,1,
	//	1, 1, 1, 1, 1, 1, 1,
	//	1, 1, 1, 1, 1, 1, 1,
	//	1, 1, 1, 1, 1, 1, 1,
	//	1, 1, 1, 1, 1, 1, 1,
	//	1, 1, 1, 1, 1, 1, 1, 
	//	1, 1, 1, 1, 1, 1, 1, };//�������˲�
	//CFilteringMask mask(7, 7, 1.0 / 49, x);
	//Mat moimg = mask.ALLProcess(&motest);
	//moimg = mcv.Matuchar2float(moimg);//�ռ���ģ����ͼ��
	////�ռ���תƵ����
	//Mat flt(7, 7, CV_8U, Scalar(1.0 / 49 * 255));

	//Mat bflt;
	//copyMakeBorder(flt, bflt, 0, motest.rows - flt.rows, 0, motest.cols - flt.cols, BORDER_CONSTANT, Scalar::all(0));
	//Mat fltdft = mcv.DFT(bflt);
	//Mat modft = mcv.DFT(moimg);

	//Mat planes[2];
	//split(fltdft, planes);


	//imshow("ԭͼ��", motest);
	//imshow("ģ����ͼ��", moimg);


	///////////////////////////////չʾ��
	//Mat mo_Wiener= mcv.DFT_Inverse_Wiener(modft, fltdft, 10);
	//imshow("ԭͼֱ��ͼ", mcv.Histogram(&motest, 256, 1024));
	//Mat zimg = mcv.IDFT(mo_Wiener, motest.rows, motest.cols, -2.2, 3);
	//imshow("ֱ��ͼ���ڽ�����ɫ", mcv.Histogram(&zimg, 256, 1024));
	//imshow("У�������˲��ɹ�", zimg);



	////////////////////    ά���˲�    ////////////////////
	/*Mat mo_Wiener_0 = mcv.DFT_Inverse_Wiener(modft, fltdft, 0);
	Mat mo_Wiener_1 = mcv.DFT_Inverse_Wiener(modft, fltdft, 1);
	Mat mo_Wiener_10 = mcv.DFT_Inverse_Wiener(modft, fltdft, 10);
	Mat mo_Wiener_100 = mcv.DFT_Inverse_Wiener(modft, fltdft, 100);
	Mat mo_Wiener_1000 = mcv.DFT_Inverse_Wiener(modft, fltdft, 1000);
	Mat mo_Wiener_10000 = mcv.DFT_Inverse_Wiener(modft, fltdft, 10000);
	Mat mo_Wiener_50000 = mcv.DFT_Inverse_Wiener(modft, fltdft, 50000);
	Mat mo_Wiener_100000 = mcv.DFT_Inverse_Wiener(modft, fltdft, 100000);
	
	imshow("ά���˲� k=0", mcv.IDFT(mo_Wiener_0, motest.rows, motest.cols, 0));
	imshow("ά���˲� k=1", mcv.IDFT(mo_Wiener_1, motest.rows, motest.cols, 0));
	imshow("ά���˲� k=10", mcv.IDFT(mo_Wiener_10, motest.rows, motest.cols, 0));
	imshow("ά���˲� k=100",  mcv.IDFT(mo_Wiener_100, motest.rows, motest.cols,0));
	imshow("ά���˲� k=1000", mcv.IDFT(mo_Wiener_1000, motest.rows, motest.cols, 0));
	imshow("ά���˲� k=100000", mcv.IDFT(mo_Wiener_10000, motest.rows, motest.cols,0));
	imshow("ά���˲� k=500000", mcv.IDFT(mo_Wiener_50000, motest.rows, motest.cols,0));
	imshow("ά���˲� k=1000000", mcv.IDFT(mo_Wiener_100000, motest.rows, motest.cols,0));*/

	////////////////////    Լ����С���˷��˲�   ////////////////////
	///*Mat mo_ICLSF_0 = mcv.DFT_Inverse_Constrained_Least_Squares_Filtering(modft, fltdft, 0);
	//Mat mo_ICLSF_01 = mcv.DFT_Inverse_Constrained_Least_Squares_Filtering(modft, fltdft, 0.1);
	//Mat mo_ICLSF_00001 = mcv.DFT_Inverse_Constrained_Least_Squares_Filtering(modft, fltdft, 0.0001);
	//Mat mo_ICLSF_0000001 = mcv.DFT_Inverse_Constrained_Least_Squares_Filtering(modft, fltdft, 0.000001);
	//Mat mo_ICLSF_0000000001 = mcv.DFT_Inverse_Constrained_Least_Squares_Filtering(modft, fltdft, 0.000000001);

	//imshow("Լ����С���˷��˲� l=0.0", mcv.IDFT(mo_ICLSF_0, motest.rows, motest.cols, 0));
	//imshow("Լ����С���˷��˲� l=0.1", mcv.IDFT(mo_ICLSF_01, motest.rows, motest.cols, 0));
	//imshow("Լ����С���˷��˲� l=0.0001", mcv.IDFT(mo_ICLSF_00001, motest.rows, motest.cols, 0));
	//imshow("Լ����С���˷��˲� l=0.000001", mcv.IDFT(mo_ICLSF_0000001, motest.rows, motest.cols, 0));
	//imshow("Լ����С���˷��˲� l=0.000000001", mcv.IDFT(mo_ICLSF_0000000001, motest.rows, motest.cols, 0));*/





	/////////////////////    ��Ե���   ͫ�׼��   /////////////////////

	//mcv.Huo_Fuyuan_transform();
	mcv.HoughLine();
	

	waitKey();
	return 0;
}