#pragma once
#define	C_E 2.718281
#define C_PI 3.141592

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



	//////Ƶ����
	Mat DFT(Mat img);//��ɢ����Ҷ�任  ����һ��˫ͨ��ͼ����ת��
	Mat IDFT(Mat dftimg, int hi, int wi, float min=-1,float max=1);//��ɢ����Ҷ���任

	Mat DFT_AmplitudeSpectrum(Mat dftimg, bool _log=true);//������
	Mat DFT_PhaseSpectrum(Mat dftimg, bool _log = true);//��λ��
	Mat DFT_RealPart(Mat dftimg, bool _log = true);//ʵ��ͼ
	Mat DFT_ImaginaryPart(Mat dftimg, bool _log = true);//�鲿ͼ

	//��װ�õĿռ��˲�����
	Mat DFT_LAPLS(Mat img);//������˹�˲�
	Mat DFT_ILPF(Mat img, float D0);//�����ͨ�˲�
	Mat DFT_BLPF(Mat img, float D0, int n);//������˹��ͨ�˲�
	Mat DFT_GLPF(Mat img, float D0);//��˹��ͨ�˲���
	Mat DFT_IHPF(Mat img, float D0);//�����ͨ�˲���
	Mat DFT_BHPF(Mat img, float D0, int n);//������˹��ͨ�˲���
	Mat DFT_GHPF(Mat img, float D0);//��˹��ͨ�˲���

	//Ƶ�����˲���
	Mat DFT_Filter(Mat dftimg, Mat filter);//�˲�����DFT����
	Mat DFT_Filter(Mat dftimg, Mat filter_Real, Mat filter_Imaginary);//�˲�����DFT����
	Mat DFT_ILPF(int hi, int wi, float D0);//�����ͨ�˲���
	Mat DFT_BLPF(int hi, int wi, float D0,int n);//������˹��ͨ�˲���
	Mat DFT_GLPF(int hi, int wi, float D0);//��˹��ͨ�˲���
	Mat DFT_IHPF(int hi, int wi, float D0);//�����ͨ�˲���
	Mat DFT_BHPF(int hi, int wi, float D0, int n);//������˹��ͨ�˲���
	Mat DFT_GHPF(int hi, int wi, float D0);//��˹��ͨ�˲���
	Mat DFT_LAPLS(int hi, int wi);//������˹�˲���

	//��¼�˲���
	Mat DFT_Filter_Inverse(Mat dftimg, Mat filter);//�˲�����DFT���˲�
	Mat DFT_Filter_Inverse(Mat dftimg, Mat filter_Real, Mat filter_Imaginary);//�˲�����DFT���˲�
	Mat DFT_Inverse_Wiener(Mat dftimg, Mat filter_dft, float k);//ά���˲�
	Mat DFT_Inverse_Constrained_Least_Squares_Filtering(Mat dftimg, Mat filter_dft, float l);//Լ����С���˷��˲�

	//����
	void Huo_Fuyuan_transform();//����Բ�任


	//��Ҫ�ڲ�ʹ��API
	int* Histogram_Group(Mat* img);//ֱ��ͼ����
	float* Cumulative(int* c, float size);//�ۻ�ֱ��ͼ����
	int GreyValue(Mat* img, bool maxormin);//��ͨ����Ҷ�ֵ
	Mat Histogram(Mat* img, int hi, int wi, float max);//��ͨ��ֱ��ͼ
	Mat Histogram_Equalization(Mat* img, float* l);//�Ҷ�ͼֱ��ͼ����

	void DFT_Filter_Show(Mat filter, char* name);//��ʾ�˲���

	//�ռ��˲���ͨ��ģ��
	int Filter_Median(Mat* img, int posx, int posy, int size);
	Mat Matuchar2float(Mat img);//��MatĬ�ϵ�UCHARת��Ϊfloat���ڿռ�����
private:
	void rect(Mat *img, Point sp, Point ep, int co);
	float PointDistance(float p1x, float p1y, float p2x, float p2y);
	Mat SChangeImgSize(Mat img, float hi, float wi);//�򵥵ķŴ���С


	Mat DFT_Rotate(Mat img);//ѡ��DFTͼ��
};

//�˲�ģ��