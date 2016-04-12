#pragma once
class CFilteringMask
{
public:
	//暂时只支持3*3和5*5的模板
	CFilteringMask(int size,float x, int* mask);
	CFilteringMask(int size, float x, vector<int>* mask);
	Mat ALLProcess(Mat* img);//用该模板处理
	float processing(Mat* img, int posx, int posy);//单像素处理
	~CFilteringMask();
private:
	int m_size=0;//模板大小
	float m_x = 1;//模板系数
	vector<int> m_mask;//模板

	void Adjustment(vector<vector<float>>* img);//调整取值范围
};

