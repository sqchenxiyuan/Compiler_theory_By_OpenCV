#pragma once
class CFilteringMask
{
public:
	//暂时只支持3*3和5*5的模板
	CFilteringMask(int s_w, int s_h, float x, int* mask);
	CFilteringMask(int s_w, int s_h, float x, float* mask);
	CFilteringMask(int s_w, int s_h, float x, vector<int>* mask);
	Mat ALLProcess(Mat* img);//用该模板处理
	float processing(Mat* img, int posx, int posy);//单像素处理
	~CFilteringMask();
private:
	int m_size_w = 0;//模板大小宽
	int m_size_h = 0;//模板大小高
	float m_x = 1;//模板系数
	vector<float> m_mask;//模板

	void Adjustment(vector<vector<float>>* img);//调整取值范围
};

