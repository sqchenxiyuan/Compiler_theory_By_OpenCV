#include "stdafx.h"
#include "FilteringMask.h"


CFilteringMask::CFilteringMask(int size, float x, int* mask)
{
	m_size = size;
	m_x = x;
	for (int i = 0; i < size*size; i++)
	{
		m_mask.push_back(mask[i]);
	}
}
CFilteringMask::CFilteringMask(int size, float x, vector<int>* mask)
{
	m_size = size;
	m_x = x;
	for (int i = 0; i < size*size; i++)
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
	Adjustment(&map);
	Mat out(hi, wi,CV_8U, Scalar(0));
	for (int i = 0; i < hi; i++)
	{
		for (int j = 0; j < wi; j++)
		{
			out.at<uchar>(i, j) = map.at(i).at(j);
		}
	}
	return out;
}

float CFilteringMask::processing(Mat* img, int posx, int posy)
{
	int wi = img->cols;
	int hi = img->rows;
	int c = (m_size - 1) / 2;
	int ji = 0;
	float s=0;//像素值总和
	//卷积
	for (int i = -c; i <= c; i++)
	{
		for (int j = -c; j <= c; j++)
		{
			int py = posy - i;
			int px = posx - j;
			if (py < 0) py = 0;
			if (px < 0) px = 0;
			if (py >= wi) py = wi-1;
			if (px >= hi) px = hi-1;
			s = s + img->at<uchar>(px, py)*m_mask.at(m_size*m_size-ji-1);
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
