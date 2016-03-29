#pragma once
class CMycv
{
public:
	CMycv();
	~CMycv();


	Mat RGB_Histogram(Mat* img, int hi, int wi);//��ͨ��ֱ��ͼ
	Mat RGB_Equalization(Mat* img);//��ͨ��ֱ��ͼ����
	Mat RGB_Gray(Mat* img,int _type);//RGBת�Ҷ�ͼ
	Mat Histogram(Mat* img, int hi, int wi);//��ͨ��ֱ��ͼ
	Mat Histogram(Mat* img, int hi, int wi,float max);//��ͨ��ֱ��ͼ


	int* Histogram_Group(Mat* img);//ֱ��ͼ����
	float* Cumulative(int* c, float size);//�ۻ�ֱ��ͼ����
	Mat Gray_Equalization(Mat* img);//�Ҷ�ͼֱ��ͼ����
	Mat Histogram_Equalization(Mat* img, float* l);


	Mat RGB_Extract(Mat* img, int p);//RGBͨ����ȡ
	Mat RGB_Synthesis(Mat* r, Mat* g, Mat* b);//3ͨ��RGB�ϳ�

	int GreyValue(Mat* img, bool maxormin);//��ͨ���Ҷ�ֵ

private:
	void rect(Mat *img, Point sp, Point ep, int co);
};

