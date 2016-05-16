#include "stdafx.h"
#include "FilteringMask.h"


CFilteringMask::CFilteringMask(int s_w, int s_h, float x, int* mask)
{
	m_size_w = s_w;
	m_size_h = s_h;
	m_x = x;
	for (int i = 0; i < s_w*s_h; i++)
	{
		m_mask.push_back(mask[i]);
		//cout << m_mask.at(i);
	}
}

CFilteringMask::CFilteringMask(int s_w, int s_h, float x, float* mask)
{
	m_size_w = s_w;
	m_size_h = s_h;
	m_x = x;
	for (int i = 0; i < s_w*s_h; i++)
	{
		m_mask.push_back(mask[i]);
		//cout << m_mask.at(i);
	}
}
CFilteringMask::CFilteringMask(int s_w, int s_h, float x, vector<int>* mask)
{
	m_size_w = s_w;
	m_size_h = s_h;
	m_x = x;
	for (int i = 0; i < s_w*s_h; i++)
	{
		m_mask.push_back(mask->at(i));
	}
}

Mat CFilteringMask::ALLProcess(Mat* img)
{
	int wi = img->cols;
	int hi = img->rows;
	vector<vector<float>> map;
	for (int i = 0; i < hi; i++)
	{
		vector<float> p1;
		map.push_back(p1);
		for (int j = 0; j < wi; j++)
		{
			map.at(i).push_back(processing(img, i, j));
		}
	}
	//Adjustment(&map);
	Mat out(hi, wi,CV_8U, Scalar(0));
	for (int i = 0; i < hi; i++)
	{
		for (int j = 0; j < wi; j++)
		{
			int x = map.at(i).at(j);
			if (x < 0) x = 0;
			if (x > 255) x = 255;
			out.at<uchar>(i, j) = x; 
		}
	}
	return out;
}

float CFilteringMask::processing(Mat* img, int posx, int posy)
{
	int wi = img->cols;
	int hi = img->rows;
	int c_w = (m_size_w - 1) / 2;
	int c_h = (m_size_h - 1) / 2;
	int ji = 1;
	float s=0;//像素值总和
	//卷积
	for (int i = -c_w; i <= c_w; i++)
	{
		for (int j = -c_h; j <= c_h; j++)
		{
			int py = posy + i;
			int px = posx + j;
			if (py < 0) py = 0;
			if (px < 0) px = 0;
			if (py >= wi) py = wi-1;
			if (px >= hi) px = hi-1;
			s = s + img->at<uchar>(px, py)*m_mask.at(m_size_w*m_size_h-ji);
			ji++;
		}
	}
	s = s*m_x;
	return s;
}


void CFilteringMask::Adjustment(vector<vector<float>>* img)
{
	int wi = img->at(0).size();
	int hi = img->size();
	float max = 0;
	float min = 256;
	for (int i = 0; i < hi; i++)
	{
		for (int j = 0; j < wi; j++)
		{
			float x = img->at(i).at(j);
			if (x > max) max = x;
			if (x < min) min = x;
		}
	}
	//cout << max << "|||" << min << endl;
	float ci = min;
	float cha = max-min;//最大最小的差
	max = 0;
	min = 256;
	for (int i = 0; i < hi; i++)
	{
		for (int j = 0; j < wi; j++)
		{
			float x = img->at(i).at(j)-ci;
			x = 255.0*(x / cha);
			img->at(i).at(j) = x;
			if (x > max) max = x;
			if (x < min) min = x;
		}
	}
	//cout << max << "|||" << min << endl;
}


CFilteringMask::~CFilteringMask()
{
}
