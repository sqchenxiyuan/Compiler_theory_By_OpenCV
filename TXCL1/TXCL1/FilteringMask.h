#pragma once
class CFilteringMask
{
public:
	//��ʱֻ֧��3*3��5*5��ģ��
	CFilteringMask(int size,float x, int* mask);
	CFilteringMask(int size, float x, vector<int>* mask);
	Mat ALLProcess(Mat* img);//�ø�ģ�崦��
	float processing(Mat* img, int posx, int posy);//�����ش���
	~CFilteringMask();
private:
	int m_size=0;//ģ���С
	float m_x = 1;//ģ��ϵ��
	vector<int> m_mask;//ģ��

	void Adjustment(vector<vector<float>>* img);//����ȡֵ��Χ
};

