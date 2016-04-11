#pragma once
class CFilteringMask
{
public:
	//暂时只支持3*3和5*5的模板
	CFilteringMask(int size, int* mask);
	CFilteringMask(int size, vector<int>* mask);
	Mat ALLProcess(Mat* img);//用该模板处理
	int processing(Mat* img,int posx,int posy);//单像素处理
	~CFilteringMask();
private:
	int m_size=0;
	vector<int> m_mask;
};

