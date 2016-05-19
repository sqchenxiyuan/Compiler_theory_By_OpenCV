#pragma once
class CFilteringMask
{
public:
	//��ʱֻ֧��3*3��5*5��ģ��
	CFilteringMask(int s_w, int s_h, float x, int* mask);
	CFilteringMask(int s_w, int s_h, float x, float* mask);
	CFilteringMask(int s_w, int s_h, float x, vector<int>* mask);
	Mat ALLProcess(Mat* img);//�ø�ģ�崦��
	float processing(Mat* img, int posx, int posy);//�����ش���
	~CFilteringMask();
private:
	int m_size_w = 0;//ģ���С��
	int m_size_h = 0;//ģ���С��
	float m_x = 1;//ģ��ϵ��
	vector<float> m_mask;//ģ��

	void Adjustment(vector<vector<float>>* img);//����ȡֵ��Χ
};

