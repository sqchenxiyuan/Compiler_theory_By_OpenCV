#include "stdafx.h"
#include "Mycv.h"


CMycv::CMycv()
{
}


CMycv::~CMycv()
{
}

/*
int:RGBͨ��ͼƬ�����ͼƬ�ĸ߶ȿ��
out:RGBͨ��ֱ��ͼ
*/
Mat CMycv::RGB_Histogram(Mat* img, int hi, int wi)
{
	Mat r = RGB_Extract(img, 2);
	Mat g = RGB_Extract(img, 1);
	Mat b = RGB_Extract(img, 0);
	int mxr = GreyValue(&r, true);
	int mxg = GreyValue(&g, true);
	int mxb = GreyValue(&b, true);
	int max = mxr;
	if (max < mxg)max = mxg;
	if (max < mxb)max = mxb;
	Mat hr = Histogram(&r, hi, wi,max);
	Mat hg = Histogram(&g, hi, wi, max);
	Mat hb = Histogram(&b, hi, wi, max);
	Mat rgb = RGB_Synthesis(&hr, &hg, &hb);
	return rgb;
}
/*
int:3ͨ��ͼƬ
out:��ֵ�����3ͨ��ͼ
*/
Mat CMycv::RGB_Equalization(Mat* img)
{
	Mat r = RGB_Extract(img, 2);
	Mat g = RGB_Extract(img, 1);
	Mat b = RGB_Extract(img, 0);
	Mat er = Gray_Equalization(&r);
	Mat eg = Gray_Equalization(&g);
	Mat eb = Gray_Equalization(&b);
	Mat rgb = RGB_Synthesis(&er, &eg, &eb);
	return rgb;
}
/*
int:3ͨ��ͼƬ  ת���㷨��1��ƽ��ֵ 2�������㷨 3�������� 4����λ�� 5��ֻȡ��ɫ��
out:�Ҷ�ͼ
*/
Mat CMycv::RGB_Gray(Mat* img, int _type)
{
	int i, j;
	int hi = img->rows, wi = img->cols;
	Mat gray(hi, wi, CV_8U, Scalar(0));
	for (i = 0; i < hi; i++)
	{
		for (j = 0; j < wi; j++)
		{
			Vec3b co=img->at<Vec3b>(i,j);
			int nc;
			switch (_type)
			{
			case 1:nc = (co[2] + co[1] + co[0]) / 3.0; break;
			case 2:nc = co[2] * 0.3 + co[1] * 0.59 + co[0] * 0.11; break;
			case 3:nc = (co[2] * 30 + co[1] * 59 + co[0] * 11) / 100; break;
			case 4:nc = (co[2] * 76 + co[1] * 151 + co[0] * 28) >> 8; break;
			case 5:nc = co[1]; break;
			default:nc = (co[2] + co[1] + co[0]) / 3.0;
				break;
			}
			gray.at<uchar>(i, j) = nc;
		}
	}
	return gray;
}
/*
int:��ͨ��ͼƬ�����ͼƬ�ĸ߶ȿ��
out:��ͨ��ֱ��ͼ
*/
Mat CMycv::Histogram(Mat* img, int hi, int wi) 
{
	int* c;
	int i, j;

	c = Histogram_Group(img);

	Mat zft(hi, wi, CV_8U, Scalar(0));

	float max = 0;
	//int i;
	for (i = 0; i < 256; i++)
	{
		if (max < c[i]) max = c[i];
	}
	for (i = 0; i < 256; i++)
	{
		rect(&zft, Point(hi*(1 - c[i] / max), wi / 256.0 * i), Point(hi - 1, wi / 256 * (i + 1) - 1), 255);
	}
	return zft;
}

/*
int:��ͨ��ͼƬ�����ͼƬ�ĸ߶ȿ��,ͼƬ��߿ɱ�ʾ�ĻҶ���
out:��ͨ��ֱ��ͼ
*/
Mat CMycv::Histogram(Mat* img, int hi, int wi, float  max)
{
	int* c;
	int i, j;

	c = Histogram_Group(img);

	Mat zft(hi, wi, CV_8U, Scalar(0));

	for (i = 0; i < 256; i++)
	{
		rect(&zft, Point(hi*(1 - c[i] / max), wi / 256.0 * i), Point(hi - 1, wi / 256 * (i + 1) - 1), 255);
	}
	delete c;
	return zft;
}
/*
int:��ͨ��ͼƬ
out:��ֵ����ĵ�ͨ��ͼ
*/
Mat  CMycv::Gray_Equalization(Mat* img)
{
	int* c;
	float *l;
	int i, j;
	c = Histogram_Group(img);
	l = Cumulative(c, img->rows*img->cols);
	return Histogram_Equalization(img, l);
}
/*
int:��ͨ��ͼƬ  �ۻ���������
out:��ֵ����ĵ�ͨ��ͼ
*/
Mat CMycv::Histogram_Equalization(Mat* img, float* l)
{
	int i, j;
	int hi = img->rows, wi = img->cols;
	Mat newimg(hi, wi, CV_8U, Scalar(0));
	for (i = 0; i < hi; i++)
	{
		for (j = 0; j < wi; j++)
		{
			newimg.at<uchar>(i, j) = l[img->at<uchar>(i,j)] * 255;
		}
	}
	return newimg;
}


/*
int:RGBͨ��ͼƬ����ȡͨ��(0 1 2)
out:��ͨ��ֱ��ͼ
*/
Mat CMycv::RGB_Extract(Mat* img, int p)
{
	int i,j; 
	int hi = img->rows;
	int wi = img->cols;
	Mat out(hi, wi, CV_8U, Scalar(0));
	for (i = 0; i < hi; i++)
	{
		for (j = 0; j < wi; j++)
		{
			out.at<uchar>(i, j) = img->at<Vec3b>(i, j)[p];
		}
	}
	return out;
}
/*
int:R G B 3��ͨ���ĵ�ͨ��ͼƬ
out:rgbͼƬ
*/
Mat CMycv::RGB_Synthesis(Mat* r, Mat* g, Mat* b)
{
	int hi=0, wi=0;
	int i,j;
	if (r->rows > hi)hi = r->rows;
	if (g->rows > hi)hi = g->rows;
	if (b->rows > hi)hi = b->rows;
	if (r->cols > wi)wi = r->cols;
	if (g->cols > wi)wi = g->cols;
	if (b->cols > wi)wi = b->cols;
	Mat rgb(hi, wi, CV_8UC3, Scalar(0, 0, 0));
	for (i = 0; i < hi; i++)
	{
		for (j = 0; j < wi; j++)
		{
			Vec3b co;
			co[0] = b->at<uchar>(i, j);
			co[1] = g->at<uchar>(i, j);
			co[2] = r->at<uchar>(i, j);
			rgb.at<Vec3b>(i, j) = co;
		}
	}
	return rgb;
}




/*
int:��ͨ��ͼƬ������������С(true_max,flase_min)
out:�����С�Ҷ�ֵ
*/
int CMycv::GreyValue(Mat* img, bool maxormin)
{
	int c[256];
	int max = 0, min = 256;
	int i,j;
	memset(c, 0, sizeof(c));

	int rs = img->rows, cs = img->cols;
	for (i = 0; i < rs; i++)
	{
		for (j = 0; j < cs; j++)
		{
			c[img->at<uchar>(i, j)]++;
		}
	}

	for (i = 0; i < 256; i++)
	{
		if (max < c[i]) max = c[i];
		if (min > c[i]) min = c[i];
	}
	if (maxormin)
	{
		return max;
	}
	return min;
}
/*
int:ֱ��ͼ����
out:�ۻ�ֱ��ͼ����
*/
float* CMycv::Cumulative(int* c, float size)
{
	int i;
	float * l = new float[256];
	for (i = 0; i < 256; i++)
	{
		l[i] = 0;
		if (i != 0)
		{
			l[i] = l[i - 1];
		}
		l[i] += c[i]/size;
	}
	return l;
}


/*
int:��ͨ��ͼƬ
out:�Ҷ�ͼ����
*/
int* CMycv::Histogram_Group(Mat* img)
{
	int* c = new int[256];
	int i, j;
	for (i = 0; i < 256; i++)
	{
		c[i] = 0;
	}

	int rs = img->rows, cs = img->cols;
	for (i = 0; i < rs; i++)
	{
		for (j = 0; j < cs; j++)
		{
			c[img->at<uchar>(i, j)]++;
		}
	}
	return c;
}


/*
int:��ͨ��ͼƬ���Խ����㣬��ɫ
*/
void CMycv::rect(Mat *img, Point sp, Point ep, int co)
{
	int i, j;
	for (i = sp.x; i <= ep.x; i++)
	{
		for (j = sp.y; j <= ep.y; j++)
		{
			//cout << sp.x << "==" << sp.y<<endl;
			//cout << ep.x << "==" << ep.y<<endl;
			img->at<uchar>(i, j) = co;
		}
	}
}