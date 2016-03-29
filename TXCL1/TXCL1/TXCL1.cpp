// TXCL1.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"


void draw_zft(int r[], int g[], int b[], char* text);
void draw_zxt(float lp[], Scalar cs);
void rect(Mat *img, Point sp, Point ep, Scalar co);
void line(Mat *img, Point sp, Point ep, Scalar co);

int _tmain(int argc, _TCHAR* argv[])
{
	CMycv mcv;

	int i, j;
	Mat img = imread("src/test1.jpg", -1);


	Mat hist = mcv.RGB_Histogram(&img, 256, 256);
	imshow("aaaa", hist);
	Mat equa = mcv.RGB_Equalization(&img);
	imshow("bbbb", equa);
	imshow("cccc", mcv.RGB_Histogram(&equa, 256, 256));

	Mat gg = mcv.RGB_Gray(&img, 1);
	imshow("g1", gg);
	imshow("gg", mcv.Gray_Equalization(&gg));
	//imshow("g2", mcv.RGB_Gray(&img, 2));
	//imshow("g3", mcv.RGB_Gray(&img, 3));
	//imshow("g4", mcv.RGB_Gray(&img, 4));
	//imshow("g5", mcv.RGB_Gray(&img, 5));

	////直方图
	//int cr[256],cg[256],cb[256];
	//memset(cr, 0, sizeof(cr));
	//memset(cg, 0, sizeof(cg));
	//memset(cb, 0, sizeof(cb));
	//int wi = img.rows;
	//int hi = img.cols;
	//for (i = 0; i < wi; i++)
	//{
	//	for (j = 0; j < hi; j++)
	//	{
	//		cr[img.at<Vec3b>(i, j)[2]]++;
	//		cg[img.at<Vec3b>(i, j)[1]]++;
	//		cb[img.at<Vec3b>(i, j)[0]]++;
	//	}
	//}
	//draw_zft(cr, cg, cb,"test1");


	////概率
	//float pr[256], pg[256], pb[256];//概率
	//float lpr[255], lpg[255], lpb[255];//累计直方图
	//memset(pr, 0, sizeof(pr));
	//memset(pg, 0, sizeof(pg));
	//memset(pb, 0, sizeof(pb));
	//memset(lpr, 0, sizeof(lpr));
	//memset(lpg, 0, sizeof(lpg));
	//memset(lpb, 0, sizeof(lpb));
	//float s = wi*hi;
	//for (i = 0; i < 256; i++)
	//{
	//	pr[i] = cr[i] / s;
	//	pg[i] = cg[i] / s;
	//	pb[i] = cb[i] / s;
	//	if (i!=0)
	//	{
	//		lpr[i] = lpr[i - 1];
	//		lpg[i] = lpg[i - 1];
	//		lpb[i] = lpb[i - 1];
	//	}
	//	lpr[i] += pr[i];
	//	lpg[i] += pg[i];
	//	lpb[i] += pb[i];
	//}
	////draw_zxt(lpr, Scalar(0,0,255));

	////均匀
	//Mat jy(wi, hi,CV_8UC3, Scalar(0,0,0));
	//for (i = 0; i < wi; i++)
	//{
	//	for (j = 0; j < hi; j++)
	//	{
	//		
	//		jy.at<Vec3b>(i, j)[2] = lpr[img.at<Vec3b>(i, j)[2]] *255;
	//		jy.at<Vec3b>(i, j)[1] = lpg[img.at<Vec3b>(i, j)[1]] * 255;
	//		//cout << i << "-" << j << endl;
	//		//cout << lpr[img.at<Vec3b>(i, j)[0]] * 255 << endl;
	//		jy.at<Vec3b>(i, j)[0] = lpb[img.at<Vec3b>(i, j)[0]] * 255;
	//		//cout << img.at<Vec3b>(i, j) << "==" << jy.at<Vec3b>(i, j) << endl;
	//	}
	//}

	////直方图
	//memset(cr, 0, sizeof(cr));
	//memset(cg, 0, sizeof(cg));
	//memset(cb, 0, sizeof(cb));
	//for (i = 0; i < wi; i++)
	//{
	//	for (j = 0; j < hi; j++)
	//	{
	//		cr[jy.at<Vec3b>(i, j)[2]]++;
	//		cg[jy.at<Vec3b>(i, j)[1]]++;
	//		cb[jy.at<Vec3b>(i, j)[0]]++;
	//	}
	//}
	//draw_zft(cr, cg, cb,"test2");

	//imshow("jy", jy);
	imshow("img", img);
	waitKey();
	return 0;
}






void draw_zft(int r[], int g[], int b[],char* text)
{
	int hi = 256;
	int wi = 256;
	Mat zft(hi, wi,CV_8UC3,Scalar(0,0,0));
	float max=0;
	int i;
	for (i = 0; i < 256; i++)
	{
		if (max < r[i]) max = r[i];
		if (max < g[i]) max = g[i];
		if (max < b[i]) max = b[i];
	}
	cout << max << endl;
	for (i = 0; i < 256; i++)
	{
		rect(&zft, Point(hi*(1 -r[i]/max), wi / 256.0 * i), Point(hi-1, wi / 256 * (i+1)-1), Scalar(0, 0, 255));
		rect(&zft, Point(hi*(1 - g[i] / max), wi / 256.0 * i), Point(hi-1, wi / 256 * (i + 1)-1), Scalar(0, 255,0));
		rect(&zft, Point(hi*(1 - b[i] / max), wi / 256.0 * i), Point(hi-1, wi / 256 * (i + 1)-1), Scalar(255, 0,0));
	}

	imshow(text, zft);
}






void draw_zxt(float lp[], Scalar cs)
{
	int hi = 256;
	int wi = 256;
	Mat zxt(hi, wi, CV_8UC3, Scalar(0, 0, 0));
	CvArr* arr = (CvArr*)&zxt;

	float max = 0;
	int i;
	for (i = 0; i < 255; i++)
	{
		Point sp = Point(hi*(1 - lp[i]), wi / 256.0 * i);
		Point ep = Point(hi*(1 - lp[i + 1]), wi / 256 * (i + 1));
		//cout << sp << "==" << ep << endl;
		line(&zxt, Point(hi*(1 - lp[i]), wi / 256.0 * i), Point(hi*(1 - lp[i+1]), wi / 256 * (i + 1)),cs);
		
	}

	imshow("累计直方图", zxt);
}








void line(Mat *img, Point sp, Point ep, Scalar co)
{
	float i, j;
	if (sp.x > ep.x)
	{
		Point c = sp;
		sp = ep;
		ep = c;
	}
	if (sp.x - ep.x != 0)
	{
		float k = (sp.y - ep.y) / (sp.x - ep.x);
		for (i = sp.x; i <= ep.x; i += 1)
		{
			j = (i - sp.x)*k + sp.y;
			//cout << sp.x << "==" << sp.y<<endl;
			//cout << ep.x << "==" << ep.y<<endl;
			img->at<Vec3b>(i, j)[0] = co[0];
			img->at<Vec3b>(i, j)[1] = co[1];
			img->at<Vec3b>(i, j)[2] = co[2];
		}
	}
	else
	{
		i = sp.x;
		for (j = sp.y; j <= ep.y; j += 1)
		{
			//cout << sp.x << "==" << sp.y<<endl;
			//cout << ep.x << "==" << ep.y<<endl;
			img->at<Vec3b>(i, j)[0] = co[0];
			img->at<Vec3b>(i, j)[1] = co[1];
			img->at<Vec3b>(i, j)[2] = co[2];
		}
	}
}


void rect(Mat *img, Point sp, Point ep, Scalar co)
{
	int i, j;
	for (i = sp.x; i <= ep.x; i++)
	{
		for (j = sp.y; j <=ep.y; j++)
		{
			//cout << sp.x << "==" << sp.y<<endl;
			//cout << ep.x << "==" << ep.y<<endl;
			img->at<Vec3b>(i, j)[0] += co[0];
			img->at<Vec3b>(i, j)[1] += co[1];
			img->at<Vec3b>(i, j)[2] += co[2];
		}
	}
}