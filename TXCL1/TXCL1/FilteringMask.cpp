#include "stdafx.h"
#include "FilteringMask.h"


CFilteringMask::CFilteringMask(int size, int* mask)
{
	m_size = size;
	for (int i = 0; i < size*size; i++)
	{
		m_mask.push_back(mask[i]);
	}
}
CFilteringMask::CFilteringMask(int size, vector<int>* mask)
{
	m_size = size;
	for (int i = 0; i < size*size; i++)
	{
		m_mask.push_back(mask->at(i));
	}
}

Mat CFilteringMask::ALLProcess(Mat* img)
{
	int wi = img->cols;
	int hi = img->rows;
	Mat out(hi, wi,CV_8U, Scalar(0));
	for (int i = 0; i < hi; i++)
	{
		for (int j = 0; j < wi; j++)
		{
			out.at<uchar>(i,j)=processing(img, i, j);
		}
	}
	return out;
}

int CFilteringMask::processing(Mat* img, int posx, int posy)
{
	int wi = img->cols;
	int hi = img->rows;
	int c = (m_size - 1) / 2;
	int ji = 0;
	int s=0;//像素值总和
	int x=0;// 权重总和
	for (int i = -c; i <= c; i++)
	{
		for (int j = -c; j <= -c; j++)
		{
			int py = posy - i;
			int px = posx - j;
			if (py < 0) py = 0;
			if (px < 0) px = 0;
			if (py >= wi) py = wi-1;
			if (px >= hi) px = hi-1;
			s = s + img->at<uchar>(px, py)*m_mask.at(ji);
			x = x + m_mask.at(ji);
			ji++;
		}
	}
	s = s / x;
	return s;
}


CFilteringMask::~CFilteringMask()
{
}
