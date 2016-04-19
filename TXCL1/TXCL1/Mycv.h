#pragma once


class CMycv
{
public:
	CMycv();
	~CMycv();

	//RGBϵ��API
	Mat RGB_Histogram(Mat* img, int hi, int wi);//��ͨ��ֱ��ͼ
	Mat RGB_Equalization(Mat* img);//��ͨ��ֱ��ͼ����
	Mat RGB_Gray(Mat* img,int _type);//RGBת�Ҷ�ͼ
	Mat RGB_Extract(Mat* img, int p);//RGBͨ����ȡ
	Mat RGB_Synthesis(Mat* r, Mat* g, Mat* b);//3ͨ��RGB�ϳ�

	//��ͨ��API
	Mat Histogram(Mat* img, int hi, int wi);//��ͨ��ֱ��ͼ
	Mat Equalization(Mat* img);//�Ҷ�ͼֱ��ͼ����
	Mat Filter_Blur_Line(Mat* img, int size_w, int size_h);//�����˲�ģ��
	Mat Filter_Median(Mat* img, int size);//��ֵ�˲�
	Mat Filter_Laplasse_operator(Mat* img, int type);//������˹����
	Mat DFT(Mat img);//��ɢ����Ҷ�任  ����һ��˫ͨ��ͼ����ת��
	Mat IDFT(Mat dftimg, int hi, int wi);//��ɢ����Ҷ���任
	Mat DFT_AmplitudeSpectrum(Mat dftimg);//������
	Mat DFT_PhaseSpectrum(Mat dftimg);//��λ��
	Mat DFT_RealPart(Mat dftimg,bool _log);//ʵ��ͼ
	Mat DFT_ImaginaryPart(Mat dftimg, bool log);//�鲿ͼ

	//��Ҫ�ڲ�ʹ��API
	int* Histogram_Group(Mat* img);//ֱ��ͼ����
	float* Cumulative(int* c, float size);//�ۻ�ֱ��ͼ����
	int GreyValue(Mat* img, bool maxormin);//��ͨ����Ҷ�ֵ
	Mat Histogram(Mat* img, int hi, int wi, float max);//��ͨ��ֱ��ͼ
	Mat Histogram_Equalization(Mat* img, float* l);//�Ҷ�ͼֱ��ͼ����

	//�˲���ͨ��ģ��
	int Filter_Median(Mat* img, int posx, int posy, int size);
private:
	void rect(Mat *img, Point sp, Point ep, int co);

	Mat DFT_Rotate(Mat img);//ѡ��DFTͼ��
};

//�˲�ģ��