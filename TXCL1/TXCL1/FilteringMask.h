#pragma once
class CFilteringMask
{
public:
	//��ʱֻ֧��3*3��5*5��ģ��
	CFilteringMask(int size, int* mask);
	CFilteringMask(int size, vector<int>* mask);
	Mat ALLProcess(Mat* img);//�ø�ģ�崦��
	int processing(Mat* img,int posx,int posy);//�����ش���
	~CFilteringMask();
private:
	int m_size=0;
	vector<int> m_mask;
};

