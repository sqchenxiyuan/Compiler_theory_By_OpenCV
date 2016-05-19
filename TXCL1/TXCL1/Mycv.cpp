#include "stdafx.h"
#include "Mycv.h"
#include "FilteringMask.h"


CMycv::CMycv()
{
}


CMycv::~CMycv()
{
}

/*
int:RGB通道图片，输出图片的高度宽度
out:RGB通道直方图
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
int:3通道图片
out:均值化后的3通道图
*/
Mat CMycv::RGB_Equalization(Mat* img)
{
	Mat r = RGB_Extract(img, 2);
	Mat g = RGB_Extract(img, 1);
	Mat b = RGB_Extract(img, 0);
	Mat er = Equalization(&r);
	Mat eg = Equalization(&g);
	Mat eb = Equalization(&b);
	Mat rgb = RGB_Synthesis(&er, &eg, &eb);
	return rgb;
}
/*
int:3通道图片  转换算法（1、平均值 2、浮点算法 3、整数法 4、移位法 5、只取绿色）
out:灰度图
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
int:单通道图片，输出图片的高度宽度
out:该通道直方图
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
int:单通道图片，输出图片的高度宽度,图片最高可表示的灰度数
out:该通道直方图
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
int:单通道图片
out:均值化后的单通道图
*/
Mat  CMycv::Equalization(Mat* img)
{
	int* c;
	float *l;
	int i, j;
	c = Histogram_Group(img);
	l = Cumulative(c, img->rows*img->cols);
	return Histogram_Equalization(img, l);
}
/*
int:单通道图片  累积概率数组
out:均值化后的单通道图
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
			if (img->type() == 0)
			{
				newimg.at<uchar>(i, j) = l[img->at<uchar>(i, j)] * 255;
			}
			else
			{
				int x = int(img->at<float>(i, j) * 255);
				if (x>255) x = 255;
				if (x<0) x = 0;
				newimg.at<uchar>(i, j) = l[x] * 255;
			}
		}
	}
	return newimg;
}


/*
int:RGB通道图片，提取通道(0 1 2)
out:该通道直方图
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
int:R G B 3个通道的单通道图片
out:rgb图片
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
int:单通道图片，输出最大还是最小(true_max,flase_min)
out:最大，最小灰度值
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
int:直方图数组
out:累积直方图数组
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
int:单通道图片
out:灰度图数组
*/
int* CMycv::Histogram_Group(Mat* img)
{
	int* c = new int[256];
	int i, j;
	for (i = 0; i < 256; i++)
	{
		c[i] = 0;
	}
	int type = img->type();
	int rs = img->rows, cs = img->cols;
	for (i = 0; i < rs; i++)
	{
		for (j = 0; j < cs; j++)
		{
			if (type == 0)
			{
				c[img->at<uchar>(i, j)]++;
			}
			else
			{
				int x = int(img->at<float>(i, j) * 255);
				if (x>255) x = 255;
				if (x<0) x = 0;
				c[x]++;
			}
		}
	}
	return c;
}


/*
int:单通道图片，对角两点，颜色
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

/*
int:单通道图片,模糊模板大小(宽高)
out:模糊后图片
*/
Mat CMycv::Filter_Blur_Line(Mat* img, int size_w, int size_h)
{
	if (size_w % 2 == 1 && size_h % 2 == 1)
	{
		int * mod = new int[size_w*size_h];
		for (int i = 0; i < size_w*size_h; i++)
		{
			mod[i] = 1;
		}
		CFilteringMask mask(size_w, size_h, 1.0 / (size_w*size_h), mod);
		return mask.ALLProcess(img);
	}
	return Mat(256,256,CV_8U,Scalar(0));
}

/*
int:单通道图片 中值滤波模板大小
out:中值滤波后图片
*/
Mat CMycv::Filter_Median(Mat* img,int size)
{
	int wi = img->cols;
	int hi = img->rows;
	Mat out(hi, wi, CV_8U, Scalar(0));
	for (int i = 0; i < hi; i++)
	{
		for (int j = 0; j < wi; j++)
		{
			out.at<uchar>(i, j) = Filter_Median(img, i, j, size);
		}
	}
	return out;
}


/*
int:单通道图片 坐标 中值滤波模板大小
out:该坐标的值
*/
int CMycv::Filter_Median(Mat* img, int posx, int posy, int size)
{
	vector<int> nums;
	int wi = img->cols;
	int hi = img->rows;
	int c = (size - 1) / 2;
	int med = 0;
	for (int i = -c; i <= c; i++)
	{
		for (int j = -c; j <= c; j++)
		{
			int py = posy - i;
			int px = posx - j;
			if (py < 0) py = 0;
			if (px < 0) px = 0;
			if (py >= wi) py = wi - 1;
			if (px >= hi) px = hi - 1;
			nums.push_back(img->at<uchar>(px, py));
		}
	}
	sort(nums.begin(), nums.end());
	return nums.at(size*size/2);
}

/*
int:单通道图片 算子大小(中心)1(9) 2(5) 3(-4) 4(-8)
out:滤波后的图
*/
Mat CMycv::Filter_Laplasse_operator(Mat* img, int type)
{
	if (type<1 || type>4) return Mat(256, 256, CV_8U, Scalar(0));


	switch (type)
	{
	case 1:{int x[] = { -1, -1, -1,
					-1, 9, -1,
					-1, -1, -1 };
		   CFilteringMask mask(3,3, 1.0, x);
		   return mask.ALLProcess(img); }
	case 2:{int x[] = { 0, -1, 0,
					-1, 5, -1,
					0, -1, 0 };
		   CFilteringMask mask(3,3, 1.0, x);
		   return mask.ALLProcess(img); }
	case 3:{int x[] = { 0, 1, 0,
					1, -4, 1,
					0, 1, 0 };
		   CFilteringMask mask(3,3, -1.0, x);
		   return mask.ALLProcess(img); }
	case 4:{int x[] = { 1, 1, 1,
					1, -8, 1,
					1, 1, 1 };
		   CFilteringMask mask(3,3, -1.0,x);
		   return mask.ALLProcess(img); }
	}
}

/*
int:单通道图片 
out:傅里叶谱
*/
Mat CMycv::DFT(Mat img)//来自opencv官网
{

	//扩展到适合FFT的尺寸
	Mat padded;                         
	int m = getOptimalDFTSize(img.rows);
	int n = getOptimalDFTSize(img.cols); // on the border add zero values

	copyMakeBorder(img, padded, 0, m - img.rows, 0, n - img.cols, BORDER_CONSTANT, Scalar::all(0));

	//扩展为实部 虚部
	Mat planes[] = { Mat_<float>(padded), Mat::zeros(padded.size(), CV_32F) };
	Mat complexI;
	//合成一张双通道图像
	merge(planes, 2, complexI);      


	//DFT变换（依然是双通道图像）
	dft(complexI, complexI);            // this way the result may fit in the source matrix

	//旋转
	complexI = DFT_Rotate(complexI);


	return complexI;
}


/*
int:傅里叶谱(双通道图) 原图像： 宽 高
out:单通道图片（反变换后的图片）
*/
Mat CMycv::IDFT(Mat dftimg, int hi, int wi, float min , float max )
{

	Mat ifft;
	dftimg = DFT_Rotate(dftimg);
	idft(dftimg, ifft, DFT_REAL_OUTPUT);


	//float min = 255;
	//float max = 0;

	//float mx=0;
	//float my=0;
	//for (int i = 0; i <hi; i++)
	//{
	//	for (int j = 0; j < wi; j++)
	//	{
	//		ifft.at<float>(i, j) = ifft.at<float>(i, j) / hi / wi;
	//		if (ifft.at<float>(i, j) < min){
	//			min = ifft.at<float>(i, j);
	//		}
	//		if (ifft.at<float>(i, j) > max)max = ifft.at<float>(i, j);
	//		if (ifft.at<float>(i, j) < 0)mx++;
	//		if (ifft.at<float>(i, j) >0)my++;
	//	}
	//}
	//cout << min <<"("<<mx<<","<<my<<")"<< "==" << max << endl;//单通道最灰度值

	//for (int i = 0; i <hi; i++)
	//{
	//	for (int j = 0; j < wi; j++)
	//	{
	//		ifft.at<float>(i, j) = (ifft.at<float>(i, j)-min)/(max-min);
	//	}
	//}



	//cout << ifft.at<float>(100, 100)<<endl;


	normalize(ifft, ifft, min, max, CV_MINMAX);
	ifft = ifft(Rect(0, 0, wi, hi));

	return ifft;
}


/*
int:DFT图像（双通道图像）
out:幅度谱
*/
Mat CMycv::DFT_AmplitudeSpectrum(Mat dftimg,bool _log)
{
	Mat planes[] = { Mat_<float>(dftimg), Mat::zeros(dftimg.size(), CV_32F) };

	//Mat test=complexI.clone();
	//idft(test, test);
	//split(test, planes);
	//magnitude(planes[0], planes[1], planes[0]);
	//imshow("test2", planes[0]);


	// compute the magnitude and switch to logarithmic scale
	// => log(1 + sqrt(Re(DFT(I))^2 + Im(DFT(I))^2))

	//拆分到2个图像
	split(dftimg, planes);                   // planes[0] = Re(DFT(I), planes[1] = Im(DFT(I))


	magnitude(planes[0], planes[1], planes[0]);// planes[0] = magnitude  


	Mat magI = planes[0];

	magI += Scalar::all(1);                    // switch to logarithmic scale
	if(_log)log(magI, magI);

	// crop the spectrum, if it has an odd number of rows or columns
	magI = magI(Rect(0, 0, magI.cols & -2, magI.rows & -2));

	// rearrange the quadrants of Fourier image  so that the origin is at the image center        

	normalize(magI, magI, 0, 1, CV_MINMAX); // Transform the matrix with float values into a 
	// viewable image form (float between values 0 and 1).

	//imshow("Input Image", img);    // Show the result
	//imshow("spectrum magnitude", magI);

	return magI;
}

/*
int:DFT图像（双通道图像）
out:相位谱
*/
Mat CMycv::DFT_PhaseSpectrum(Mat dftimg,bool _log)
{
	Mat planes[] = { Mat_<float>(dftimg), Mat::zeros(dftimg.size(), CV_32F) };

	//拆分到2个图像
	split(dftimg, planes);                   // planes[0] = Re(DFT(I), planes[1] = Im(DFT(I))

	int hi = dftimg.rows;
	int wi = dftimg.cols;
	for (int i = 0; i < hi; i++)
	{
		for (int j = 0; j < wi; j++)
		{
			planes[0].at<float>(i, j) = atan(planes[1].at<float>(i, j) / planes[0].at<float>(i, j));
		}
	}
	Mat magI = planes[0];

	magI += Scalar::all(1);                    // switch to logarithmic scale
	if (_log)log(magI, magI);

	// crop the spectrum, if it has an odd number of rows or columns
	magI = magI(Rect(0, 0, magI.cols & -2, magI.rows & -2));

	// rearrange the quadrants of Fourier image  so that the origin is at the image center        

	normalize(magI, magI, 0, 1, CV_MINMAX); // Transform the matrix with float values into a 
	// viewable image form (float between values 0 and 1).

	//imshow("Input Image", img);    // Show the result
	//imshow("spectrum magnitude", magI);

	return magI;
}

/*
int:DFT图像（双通道图像）
out:实部谱
*/
Mat CMycv::DFT_RealPart(Mat dftimg, bool _log)
{
	Mat planes[] = { Mat_<float>(dftimg), Mat::zeros(dftimg.size(), CV_32F) };

	//拆分到2个图像
	split(dftimg, planes);                   // planes[0] = Re(DFT(I), planes[1] = Im(DFT(I))

	Mat magI = planes[0];
	if(_log) log(magI, magI);
	magI += Scalar::all(1);                    // switch to logarithmic scale

	magI = magI(Rect(0, 0, magI.cols & -2, magI.rows & -2));
     

	normalize(magI, magI, 0, 1, CV_MINMAX); // Transform the matrix with float values into a 

	return magI;
}

/*
int:DFT图像（双通道图像）
out:虚部谱
*/
Mat CMycv::DFT_ImaginaryPart(Mat dftimg, bool _log)
{
	Mat planes[] = { Mat_<float>(dftimg), Mat::zeros(dftimg.size(), CV_32F) };

	//拆分到2个图像
	split(dftimg, planes);                   // planes[0] = Re(DFT(I), planes[1] = Im(DFT(I))

	Mat magI = planes[1];
	if (_log) log(magI, magI);
	magI += Scalar::all(1);                    // switch to logarithmic scale

	magI = magI(Rect(0, 0, magI.cols & -2, magI.rows & -2));
	normalize(magI, magI, 0, 1, CV_MINMAX);

	return magI;
}



/*
int:待旋转图像
out:旋转后图像
*/
Mat CMycv::DFT_Rotate(Mat img)
{
	Mat _magI = img.clone();
	// rearrange the quadrants of Fourier image  so that the origin is at the image center        
	int cx = img.cols / 2;
	int cy = img.rows / 2;

	Mat q0(_magI, Rect(0, 0, cx, cy));   // Top-Left - Create a ROI per quadrant 
	Mat q1(_magI, Rect(cx, 0, cx, cy));  // Top-Right
	Mat q2(_magI, Rect(0, cy, cx, cy));  // Bottom-Left
	Mat q3(_magI, Rect(cx, cy, cx, cy)); // Bottom-Right

	Mat tmp;                           // swap quadrants (Top-Left with Bottom-Right)
	q0.copyTo(tmp);
	q3.copyTo(q0);
	tmp.copyTo(q3);

	q1.copyTo(tmp);                    // swap quadrant (Top-Right with Bottom-Left)
	q2.copyTo(q1);
	tmp.copyTo(q2);

	return _magI;
}

/*
int:DFT图像（双通道图像） 滤波器图像
out:过滤后图像
*/
Mat CMycv::DFT_Filter(Mat dftimg, Mat filter)
{
	int hi = dftimg.rows;
	int wi = dftimg.cols;

	Mat out;
	Mat planes[2];


	//imshow("aaaaa", DFT_AmplitudeSpectrum(dftimg));

	split(dftimg, planes);

	for (int i = 0; i < hi; i++)
	{
		for (int j = 0; j < wi; j++)
		{
			planes[0].at<float>(i, j) = planes[0].at<float>(i, j)* filter.at<float>(i, j);
			planes[1].at<float>(i, j) = planes[1].at<float>(i, j)* filter.at<float>(i, j);
		}
	}

	merge(planes, 2, out);

	//imshow("bbbbb", DFT_AmplitudeSpectrum(out));


	return  out;
}


/*
int:DFT图像（双通道图像） 滤波器实部图像  滤波器虚部图像
out:过滤后图像
*/
Mat CMycv::DFT_Filter(Mat dftimg, Mat filter_Real, Mat filter_Imaginary)
{
	int hi = dftimg.rows;
	int wi = dftimg.cols;

	Mat out;
	Mat planes[2];


	//imshow("aaaaa", DFT_AmplitudeSpectrum(dftimg));

	split(dftimg, planes);

	for (int i = 0; i < hi; i++)
	{
		for (int j = 0; j < wi; j++)
		{
			float a = planes[0].at<float>(i, j);
			float b = planes[1].at<float>(i, j);
			float c = filter_Real.at<float>(i, j);
			float d = filter_Imaginary.at<float>(i, j);


			planes[0].at<float>(i, j) = a*c - b*d;
			planes[1].at<float>(i, j) = a*d + b*c;
		}
	}

	merge(planes, 2, out);

	//imshow("bbbbb", DFT_AmplitudeSpectrum(out));


	return  out;
}


Mat CMycv::DFT_Filter_Inverse(Mat dftimg, Mat filter)
{
	int hi = dftimg.rows;
	int wi = dftimg.cols;

	Mat out;
	Mat planes[2];


	//imshow("aaaaa", DFT_AmplitudeSpectrum(dftimg));

	split(dftimg, planes);

	for (int i = 0; i < hi; i++)
	{
		for (int j = 0; j < wi; j++)
		{
			if (filter.at<float>(i, j)>0.0000001 || filter.at<float>(i, j)<-0.0000001)
			{
				planes[0].at<float>(i, j) = planes[0].at<float>(i, j) / filter.at<float>(i, j);
				planes[1].at<float>(i, j) = planes[1].at<float>(i, j) / filter.at<float>(i, j);
			}
			//cout << planes[0].at<float>(i, j) << "==" << planes[1].at<float>(i, j) << endl;
		}
	}

	merge(planes, 2, out);

	//imshow("bbbbb", DFT_AmplitudeSpectrum(out));


	return  out;
}


Mat CMycv::DFT_Filter_Inverse(Mat dftimg, Mat filter_Real, Mat filter_Imaginary)
{
	int hi = dftimg.rows;
	int wi = dftimg.cols;

	Mat out;
	Mat planes[2];


	//imshow("aaaaa", DFT_AmplitudeSpectrum(dftimg));

	split(dftimg, planes);

	for (int i = 0; i < hi; i++)
	{
		for (int j = 0; j < wi; j++)
		{
			float a = planes[0].at<float>(i, j);
			float b = planes[1].at<float>(i, j);
			float c = filter_Real.at<float>(i, j);
			float d = filter_Imaginary.at<float>(i, j);
			float m = c*c + d*d;

			planes[0].at<float>(i, j) = (a*c + b*d)/m;
			planes[1].at<float>(i, j) = (b*c-a*d)/m;
		}
	}

	merge(planes, 2, out);

	//imshow("bbbbb", DFT_AmplitudeSpectrum(out));


	return  out;
}

/*
int:DFT图像（双通道图像）的宽高   D0
out:滤波器
*/
Mat CMycv::DFT_ILPF(int hi,int wi, float D0)
{
	Mat filter(hi,wi,CV_32F,Scalar(0));
	for (int i = 0; i < hi; i++)
	{
		for (int j = 0; j < wi; j++)
		{
			if (PointDistance(i, j, hi / 2, wi / 2) <= D0) filter.at<float>(i, j) = 1;
			else filter.at<float>(i, j) = 0;
		}
	}
	return  filter;
}

/*
int:DFT图像（双通道图像）的宽高   D0	n阶数
out:滤波器
*/
Mat CMycv::DFT_BLPF(int hi, int wi, float D0,int n)
{
	Mat filter(hi, wi, CV_32F, Scalar(0));
	for (int i = 0; i < hi; i++)
	{
		for (int j = 0; j < wi; j++)
		{
			filter.at<float>(i, j) = 1 / (1 + powf((PointDistance(i, j, hi / 2, wi / 2) / D0), 2 * n));
			
		}
	}
	return  filter;
}

/*
int:DFT图像（双通道图像）的宽高   D0
out:滤波器
*/
Mat CMycv::DFT_GLPF(int hi, int wi, float D0)
{
	Mat filter(hi, wi, CV_32F, Scalar(0));
	for (int i = 0; i < hi; i++)
	{

		for (int j = 0; j < wi; j++)
		{
			float d = PointDistance(i, j, hi / 2, wi / 2);
			filter.at<float>(i, j) = powf(C_E, -1 * (d / D0)*(d / D0) / 2);
		}
	}
	//cout << filter.at<float>(100, 100) << "==" << d << "==" << -1*(d / D0)*(d / D0)/2 << endl;
	return  filter;
}

/*
int:DFT图像（双通道图像）的宽高   D0
out:滤波器
*/
Mat CMycv::DFT_IHPF(int hi, int wi, float D0)
{
	Mat filter(hi, wi, CV_32F, Scalar(0));
	for (int i = 0; i < hi; i++)
	{
		for (int j = 0; j < wi; j++)
		{
			if (PointDistance(i, j, hi / 2, wi / 2) > D0) filter.at<float>(i, j) = 1;
			else filter.at<float>(i, j) = 0;
		}
	}
	return  filter;
}

/*
int:DFT图像（双通道图像）的宽高   D0	n阶数
out:滤波器
*/
Mat CMycv::DFT_BHPF(int hi, int wi, float D0, int n)
{
	Mat filter(hi, wi, CV_32F, Scalar(0));
	for (int i = 0; i < hi; i++)
	{
		for (int j = 0; j < wi; j++)
		{
			filter.at<float>(i, j) = 1.0 / (1 + powf((D0 / PointDistance(i, j, hi / 2, wi / 2)), 2 * n));

		}
	}
	return  filter;
}
/*
int:DFT图像（双通道图像）的宽高   D0
out:滤波器
*/
Mat CMycv::DFT_GHPF(int hi, int wi, float D0)
{
	Mat filter(hi, wi, CV_32F, Scalar(0));
	for (int i = 0; i < hi; i++)
	{
		for (int j = 0; j < wi; j++)
		{
			float d = PointDistance(i, j, hi / 2, wi / 2);
			filter.at<float>(i, j) = 1 - powf(C_E, -1 * (d / D0) / 2 * (d / D0));
		}
	}
	return  filter;
}

/*
int:DFT图像（双通道图像）的宽高  
out:滤波器
*/
Mat CMycv::DFT_LAPLS(int hi, int wi)
{
	Mat filter(hi, wi, CV_32F, Scalar(0));
	for (int i = 0; i < hi; i++)
	{
		for (int j = 0; j < wi; j++)
		{
			float d = PointDistance(i, j, hi / 2, wi / 2);
			filter.at<float>(i, j) = -4*C_PI*C_PI*d*d ;
		}
	}
	return  filter;
}

void CMycv::DFT_Filter_Show(Mat filter, char* name)
{
	normalize(filter, filter, 0, 1, CV_MINMAX);
	imshow(name, filter);
}

/*
int:两点坐标
out:距离
*/
float CMycv::PointDistance(float p1x, float p1y, float p2x, float p2y)
{
	float x = p1x - p2x;
	float y = p1y - p2y;
	return sqrt(x*x + y*y);
}

/*
int:需要处理的图像
out:拉不拉斯滤波处理后的图像
*/
Mat CMycv::DFT_LAPLS(Mat img)
{
	Mat dft = DFT(img);
	Mat filt = DFT_LAPLS(dft.rows, dft.cols);
	
	//DFT_Filter_Show(filt, "filt");
	//imshow(" 频率域拉不拉斯滤波器DFT", DFT_AmplitudeSpectrum(DFT(filt)))

	Mat filt_idft = DFT_Filter(dft, filt);
	Mat idft = IDFT(filt_idft, img.rows, img.cols);

	int hi = img.rows;
	int wi = img.cols;
	Mat out(hi, wi, CV_8U, Scalar(0));
	for (int i = 0; i < hi; i++)
	{
		for (int j = 0; j < wi; j++)
		{
			int x = img.at<uchar>(i, j) - idft.at<float>(i, j) * 255 ;
			if (x < 0) x = 0;
			if (x > 255) x = 255;
			out.at<uchar>(i, j) = x;
		}
	}

	return out;
}

/*
int:需要处理的图像  理想低通滤波D0
out:理想低通滤波处理后的图像
*/
Mat CMycv::DFT_ILPF(Mat img, float D0)
{
	Mat dft = DFT(img);
	Mat filt = DFT_ILPF(dft.rows, dft.cols, D0);
	Mat dft_ilpf = DFT_Filter(dft, filt);
	Mat idft = IDFT(dft_ilpf, img.rows, img.cols,0);

	return idft;
}

/*
int:需要处理的图像  布特沃斯低通滤波D0  阶数n
out:布特沃斯低通滤波处理后的图像
*/
Mat CMycv::DFT_BLPF(Mat img, float D0, int n)
{
	Mat dft = DFT(img);
	Mat filt = DFT_BLPF(dft.rows, dft.cols, D0,n);
	Mat dft_ilpf = DFT_Filter(dft, filt);
	Mat idft = IDFT(dft_ilpf, img.rows, img.cols,0);

	return idft;
}

/*
int:需要处理的图像  高斯低通滤波器D0 
out:高斯低通滤波器处理后的图像
*/
Mat CMycv::DFT_GLPF(Mat img, float D0)
{
	Mat dft = DFT(img);
	Mat filt = DFT_GLPF(dft.rows, dft.cols, D0);
	Mat dft_ilpf = DFT_Filter(dft, filt);
	Mat idft = IDFT(dft_ilpf, img.rows, img.cols,0);

	return idft;
}

/*
int:需要处理的图像  理想高通滤波D0 
out:理想高通滤波处理后的图像
*/
Mat CMycv::DFT_IHPF(Mat img, float D0)
{
	Mat dft = DFT(img);
	Mat filt = DFT_IHPF(dft.rows, dft.cols, D0);
	Mat dft_ilpf = DFT_Filter(dft, filt);
	Mat idft = IDFT(dft_ilpf, img.rows, img.cols);

	return idft;
}

/*
int:需要处理的图像  布特沃斯高通滤波D0  阶数n
out:布特沃斯高通滤波处理后的图像
*/
Mat CMycv::DFT_BHPF(Mat img, float D0, int n)
{
	Mat dft = DFT(img);
	Mat filt = DFT_BHPF(dft.rows, dft.cols, D0,n);
	Mat dft_ilpf = DFT_Filter(dft, filt);
	Mat idft = IDFT(dft_ilpf, img.rows, img.cols);

	return idft;
}

/*
int:需要处理的图像  高斯高通滤波D0 
out:高斯高通滤波处理后的图像
*/
Mat CMycv::DFT_GHPF(Mat img, float D0)
{
	Mat dft = DFT(img);
	Mat filt = DFT_GHPF(dft.rows, dft.cols, D0);
	Mat dft_ilpf = DFT_Filter(dft, filt);
	Mat idft = IDFT(dft_ilpf, img.rows, img.cols);

	return idft;
}


Mat CMycv::Matuchar2float(Mat img)
{
	int hi = img.rows;
	int wi = img.cols;
	Mat out(hi,wi, CV_32F);

	for (int i = 0; i < hi; i++)
	{
		for (int j = 0; j < wi; j++)
		{
			out.at<float>(i, j) = img.at<uchar>(i,j) / 255.0;
		}
	}
	return out;
}


Mat CMycv::SChangeImgSize(Mat img, float hi, float wi)
{

	Mat out(hi, wi, CV_8U, Scalar(0));
	for (int i = 0; i < hi; i++)
	{
		for (int j = 0; j < wi; j++)
		{
			out.at<uchar>(i, j) = img.at<uchar>(i*img.rows/hi,j*img.cols/wi);
		}
	}
	return out;
}


Mat CMycv::DFT_Inverse_Wiener(Mat dftimg, Mat filter_dft, float k)
{
	int hi = dftimg.rows;
	int wi = dftimg.cols;

	Mat out;
	Mat planes[2];
	Mat filter[2];
	split(filter_dft, filter);//处理滤波的频率域域与实部虚部
	Mat filter_Real = filter[0];
	Mat	filter_Imaginary = filter[1];

	split(dftimg, planes);

	for (int i = 0; i < hi; i++)
	{
		for (int j = 0; j < wi; j++)
		{
			float a = planes[0].at<float>(i, j);
			float b = planes[1].at<float>(i, j);
			float c = filter_Real.at<float>(i, j);
			float d = filter_Imaginary.at<float>(i, j);
			float m = c*c + d*d;

			if (m < 0.000001 || m>1000000)continue;
			planes[0].at<float>(i, j) = (a*c + b*d) / (m+k);
			planes[1].at<float>(i, j) = (b*c - a*d) / (m+k);
		}
	}

	merge(planes, 2, out);

	//imshow("bbbbb", DFT_AmplitudeSpectrum(out));


	return  out;
}


Mat CMycv::DFT_Inverse_Constrained_Least_Squares_Filtering(Mat dftimg, Mat filter_dft, float l)
{
	Mat P = DFT_LAPLS(dftimg.rows, dftimg.cols);

	int hi = dftimg.rows;
	int wi = dftimg.cols;

	Mat out;
	Mat planes[2];
	Mat filter[2];
	split(filter_dft, filter);//处理滤波的频率域域与实部虚部
	Mat filter_Real = filter[0];
	Mat	filter_Imaginary = filter[1];

	split(dftimg, planes);

	for (int i = 0; i < hi; i++)
	{
		for (int j = 0; j < wi; j++)
		{
			float a = planes[0].at<float>(i, j);
			float b = planes[1].at<float>(i, j);
			float c = filter_Real.at<float>(i, j);
			float d = filter_Imaginary.at<float>(i, j);
			float m = c*c + d*d;

			float p2 = P.at<float>(i, j)*P.at<float>(i, j);
			p2 = p2*l;
			float m_p = m + p2;

			planes[0].at<float>(i, j) = (a*c + b*d) /m_p;
			planes[1].at<float>(i, j) = (b*c - a*d) /m_p;
		}
	}

	merge(planes, 2, out);

	//imshow("bbbbb", DFT_AmplitudeSpectrum(out));


	return  out;
}


void CMycv::Huo_Fuyuan_transform()//网上霍夫圆检测测试用例
{
	IplImage* image0 = cvLoadImage("src/瞳孔检测示例.jpg", CV_LOAD_IMAGE_GRAYSCALE);
	IplImage* image = cvLoadImage("src/瞳孔检测示例.jpg", CV_LOAD_IMAGE_GRAYSCALE);
	//IplImage* image=NULL;//  
	//image=cvCreateImage(cvGetSize(image0),IPL_DEPTH_8U,3);   
	CvMemStorage* storage = cvCreateMemStorage(0);
	cvSmooth(image0, image, CV_GAUSSIAN, 9, 9);
	CvSeq* results = cvHoughCircles(image, storage, CV_HOUGH_GRADIENT, 2, image->width / 10);
	for (int i = 0; i<results->total; i++)
	{
		float* p = (float*)cvGetSeqElem(results, i);
		CvPoint pt = cvPoint(cvRound(p[0]), cvRound(p[1]));
		cvCircle(image, pt, cvRound(p[2]), CV_RGB(0xff, 0xff, 0xff));
	}
	cvNamedWindow("source", 0);
	cvShowImage("source", image0);
	cvNamedWindow("cvHoughCircles", 0);
	cvShowImage("cvHoughCircles", image);
}

Mat CMycv::HoughCircl(Mat img, float min_r, float max_r, float d_r, float min_angle)
{
	//imshow("原图", img);
	cout << "转化灰度图..." << endl;
	Mat img_gray = RGB_Gray(&img,1);
	//imshow("灰度图", img_gray);
	cout << "Canny处理..." << endl;
	Mat img_canny = Canny(img_gray,9,10);
	//imshow("canny处理后", img_canny);

	cout << "霍夫圆处理中..." << endl;
	vector<C_circle> circles = HoughCircl(img, img_canny, min_r, max_r, d_r, min_angle, 2);

	cout << "寻找最大重叠" << endl;
	Mat out=img.clone();
	int s = circles.size();

	if (s == 0){
		cout << "没有找到合适的圆，请改变参数!" << endl;
		return img;
	}

	int max=0;
	for (int i = 0; i < s; i++)
	{
		C_circle c = circles.at(i);
		if (circles.at(i).wight>circles.at(max).wight) max = i;
	}
	C_circle c = circles.at(max);


	cout << "画圆中" << endl;
	circle(&out, c.pos, c.r, c.size, Scalar(0, 0, 255));


	return out;
	//imshow("圆处理", out);
}

Mat CMycv::Filter_Gaussian_Blur(Mat img, int size,float o)
{
	//获取高斯模糊模板
	float * mask = new float[size*size];
	int size1 = size / 2;
	float o2 = 2 * o*o;

	int ji = 0;
	float s = 0;
	for (int i = -size1; i <=size1; i++)
	{
		for (int j = -size1; j <=size1; j++)
		{
			mask[ji] = powf(C_E, -(i*i + j*j) / o2) / o2* C_PI;
			s += mask[ji];
			ji++;
		}
	}
	for (int i = 0; i < size*size; i++)
	{
		mask[i] /= s;
	}

	//对图像模糊
	CFilteringMask mask2(size, size, 1.0, mask);
	return mask2.ALLProcess(&img);
}

Mat CMycv::Canny(Mat img,float g_size,float f_o){

	//模糊处理
	Mat img_g = Filter_Gaussian_Blur(img, g_size, f_o);
	//imshow("高斯模糊后", img_g);

	//计算图像梯度及其方向
	Mat img_x = Canny_get_x(img_g);
	Mat img_y = Canny_get_y(img_g);
	Mat img_M = Canny_get_gradient(img_x, img_y);//梯度
	Mat img_T = Canny_get_position(img_x, img_y);//方向

	/*cout << img_x.at<float>(10, 10) << endl;
	cout << img_y.at<float>(10, 10) << endl;
	cout << img_M.at<float>(10, 10) << endl;
	cout << img_T.at<float>(10, 10) << endl;*/

	//非极大值抑制
	Mat img_N= Canny_nonmaximumsuppression(img_x, img_y, img_M, img_T);

	Mat img_out = Canny_doublethresholddetection(img_M, img_N);

	return img_out;
}

Mat CMycv::Canny_get_x(Mat img)
{
	int h = img.rows;
	int w = img.cols;
	Mat out(h, w, CV_32F);
	for (int i = 0; i < h; i++)
	{
		for (int j = 0; j < w; j++)
		{
			float x1=0, x2=0;
			x1 = img.at<uchar>(i, j);
			x2 = x1;
			if (i + 1 < h) x2 = img.at<uchar>(i + 1, j);


			out.at<float>(i,j) = x2 - x1;

			if (j+1 < w ){
				x1 = img.at<uchar>(i, j+1);
				x2 = x1;
				if (i + 1 < h) x2 = img.at<uchar>(i + 1, j + 1);

				out.at<float>(i, j) = ( out.at<float>(i, j) + x2 - x1) / 2;
			}

		}
	}
	return out;
}

Mat CMycv::Canny_get_y(Mat img)
{
	int h = img.rows;
	int w = img.cols;
	Mat out(h, w, CV_32F);
	for (int i = 0; i < h; i++)
	{
		for (int j = 0; j < w; j++)
		{
			float x1=0, x2=0;
			x1 = img.at<uchar>(i, j);
			x2 = x1;
			if (j + 1 < w) x2 = img.at<uchar>(i, j+1);


			out.at<float>(i, j) = x2 - x1;

			if (i + 1 < h){
				x1 = img.at<uchar>(i+1, j);
				x2 = x1;
				if (j + 1 < w) x2 = img.at<uchar>(i + 1, j + 1);

				out.at<float>(i, j) = (out.at<float>(i, j) + x2 - x1) / 2;
			}
		}
	}
	return out;
}

Mat CMycv::Canny_get_gradient(Mat x, Mat y)
{
	int h = x.rows;
	int w = x.cols;
	Mat out(h, w, CV_32F);
	for (int i = 0; i < h; i++)
	{
		for (int j = 0; j < w; j++)
		{
			float x1 = x.at<float>(i, j);
			float x2 = y.at<float>(i, j);
			out.at<float>(i, j) =sqrt(x1*x1+x2*x2);
		}
	}
	return out;
}

Mat CMycv::Canny_get_position(Mat x, Mat y)
{
	int h = x.rows;
	int w = x.cols;
	Mat out(h, w, CV_32F);
	for (int i = 0; i < h; i++)
	{
		for (int j = 0; j < w; j++)
		{
			float x1 = x.at<float>(i, j);
			float x2 = y.at<float>(i, j);
			out.at<float>(i, j) = atan2(x1,x2)/C_PI*360;
			if (out.at<float>(i, j)<0)
			{
				out.at<float>(i, j) += 360;
			}

		}
	}
	return out;
}

Mat CMycv::Canny_nonmaximumsuppression(Mat X, Mat Y, Mat M, Mat T)
{
	int h = M.rows;
	int w = M.cols;
	int g1 = 0, g2 = 0, g3 = 0, g4 = 0;                            //用于进行插值，得到亚像素点坐标值  
	double dTmp1 = 0.0, dTmp2 = 0.0;                           //保存两个亚像素点插值得到的灰度数据  
	double dWeight = 0.0;

	Mat out(h, w, CV_8U);

	for (int i = 0; i < h; i++)
	{
		out.at<uchar>(i, 0) = 0;
		out.at<uchar>(i, w - 1) = 0;
	}
	for (int i = 0; i < w; i++)
	{
		out.at<uchar>(0, i) = 0;
		out.at<uchar>(h - 1, i) = 0;
	}


	for (int i = 1; i < h-1; i++)
	{
		for (int j = 1; j < w-1; j++)
		{
			float x = M.at<float>(i, j);
			if (M.at<float>(i, j) < 0.0000001 && M.at<float>(i, j)>-0.000001 || M.at<float>(i, j)==0)
				out.at<uchar>(i, j) = 0;         //如果当前梯度幅值为0，则不是局部最大对该点赋为0  
			else
			{
				////////首先判断属于那种情况，然后根据情况插值///////  
				////////////////////第一种情况///////////////////////  
				/////////       g1  g2                  /////////////  
				/////////           C                   /////////////  
				/////////           g3  g4              /////////////  
				/////////////////////////////////////////////////////  
				if (((T.at<float>(i,j) >= 90) && (T.at<float>(i,j)<135)) ||
					((T.at<float>(i,j) >= 270) && (T.at<float>(i,j)<315)))
				{
					//////根据斜率和四个中间值进行插值求解  
					g1 = M.at<float>(i - 1, j - 1);
					g2 = M.at<float>(i-1, j);
					g3 = M.at<float>(i+1, j);
					g4 = M.at<float>(i+1, j+1);
					dWeight = fabs(X.at<float>(i, j)) / fabs(Y.at<float>(i, j));   //反正切  
					dTmp1 = g1*dWeight + g2*(1 - dWeight);
					dTmp2 = g4*dWeight + g3*(1 - dWeight);
				}
				////////////////////第二种情况///////////////////////  
				/////////       g1                      /////////////  
				/////////       g2  C   g3              /////////////  
				/////////               g4              /////////////  
				/////////////////////////////////////////////////////  
				else if (((T.at<float>(i,j) >= 135) && (T.at<float>(i,j)<180)) ||
					((T.at<float>(i,j) >= 315) && (T.at<float>(i,j)<360)))
				{
					g1 = M.at<float>(i - 1, j - 1);
					g2 = M.at<float>(i, j - 1);
					g3 = M.at<float>(i , j + 1);
					g4 = M.at<float>(i + 1, j + 1);
					dWeight = fabs(Y.at<float>(i, j)) / fabs(X.at<float>(i, j));   //正切  
					dTmp1 = g2*dWeight + g1*(1 - dWeight);
					dTmp2 = g4*dWeight + g3*(1 - dWeight);
				}
				////////////////////第三种情况///////////////////////  
				/////////           g1  g2              /////////////  
				/////////           C                   /////////////  
				/////////       g4  g3                  /////////////  
				/////////////////////////////////////////////////////  
				else if (((T.at<float>(i,j) >= 45) && (T.at<float>(i,j)<90)) ||
					((T.at<float>(i,j) >= 225) && (T.at<float>(i,j)<270)))
				{
					g1 = M.at<float>(i - 1, j);
					g2 = M.at<float>(i - 1, j +1);
					g3 = M.at<float>(i +1, j - 1);
					g4 = M.at<float>(i + 1, j );
					dWeight = fabs(X.at<float>(i, j)) / fabs(Y.at<float>(i, j));   //反正切  
					dTmp1 = g2*dWeight + g1*(1 - dWeight);
					dTmp2 = g3*dWeight + g4*(1 - dWeight);
				}
				////////////////////第四种情况///////////////////////  
				/////////               g1              /////////////  
				/////////       g4  C   g2              /////////////  
				/////////       g3                      /////////////  
				/////////////////////////////////////////////////////  
				else if (((T.at<float>(i,j) >= 0) && (T.at<float>(i,j)<45)) ||
					((T.at<float>(i,j) >= 180) && (T.at<float>(i,j)<225)))
				{
					g1 = M.at<float>(i - 1, j+1);
					g2 = M.at<float>(i , j+1);
					g3 = M.at<float>(i +1, j-1);
					g4 = M.at<float>(i, j-1);
					dWeight = fabs(Y.at<float>(i, j)) / fabs(X.at<float>(i, j));   //正切  
					dTmp1 = g1*dWeight + g2*(1 - dWeight);
					dTmp2 = g3*dWeight + g4*(1 - dWeight);
				}

				//////////进行局部最大值判断，并写入检测结果////////////////  
				if (M.at<float>(i, j) >= dTmp1&& M.at<float>(i, j) >= dTmp2)
					out.at<uchar>(i, j) = 128;
				else
					out.at<uchar>(i, j) = 0;
			}
		}
	}
	return out;
}

Mat CMycv::Canny_doublethresholddetection(Mat M, Mat N)
{

	int h = N.rows;
	int w = N.cols;

	int nHist[1024];
	int nEdgeNum;             //可能边界数  
	int nMaxMag = 0;          //最大梯度数  
	int nHighCount;

	for (int i = 0; i<1024; i++)
		nHist[i] = 0;
	for (int i = 0; i<h; i++)
	{
		for (int j = 0; j<w; j++)
		{
			if (N.at<uchar>(i, j) == 128)
				nHist[int(M.at<float>(i, j))]++;
		}
	}

	//获取最大梯度幅值及潜在边缘点个数
	nEdgeNum = nHist[0];
	nMaxMag = 0;                    //获取最大的梯度值        
	for (int i = 1; i<1024; i++)           //统计经过“非最大值抑制”后有多少像素  
	{
		if (nHist[i] != 0)       //梯度为0的点是不可能为边界点的  
		{
			nMaxMag = i;
		}
		nEdgeNum += nHist[i];   //经过non-maximum suppression后有多少像素  
	}
	
	//计算两个阈值
	double  dRatHigh = 0.79;
	double  dThrHigh;
	double  dThrLow;
	double  dRatLow = 0.5;
	nHighCount = (int)(dRatHigh * nEdgeNum + 0.5);
	int j = 1;
	nEdgeNum = nHist[1];
	while ((j<(nMaxMag - 1)) && (nEdgeNum < nHighCount))
	{
		j++;
		nEdgeNum += nHist[j];
	}
	dThrHigh = j;                                   //高阈值  
	dThrLow = (int)((dThrHigh)* dRatLow + 0.5);    //低阈值  

	//进行边缘检测
	for (int i = 0; i<h; i++)
	{
		for (int j = 0; j<w; j++)
		{
			if ((N.at<uchar>(i, j) == 128) && (M.at<float>(i, j) >= dThrHigh))
			{
				N.at<uchar>(i, j) = 255;
				TraceEdge(i, j, dThrLow, &N, &M);
			}
		}
	}
	
	//去除多余的点
	for (int i = 0; i<h; i++)
	{
		for (int j = 0; j<w; j++)
		{
			if (N.at<uchar>(i, j) == 128)
			{
				N.at<uchar>(i, j) = 0;
			}
		}
	}

	return N;

}

void CMycv::TraceEdge(int y, int x, int nThrLow, Mat* N, Mat* M)
{
	int h = N->rows;
	int w = N->cols;
	//对8邻域像素进行查询  
	int xNum[8] = { 1, 1, 0, -1, -1, -1, 0, 1 };
	int yNum[8] = { 0, 1, 1, 1, 0, -1, -1, -1 };
	int k;
	int yy, xx;
	for (k = 0; k<8; k++)
	{
		yy = y + yNum[k];
		xx = x + xNum[k];

		if (yy < 0||yy>=h||xx<0||x>=w) continue;

		if (N->at<uchar>(yy, xx) == 128 && M->at<float>(yy, xx) >= nThrLow)
		{
			//该点设为边界点  
			N->at<uchar>(yy, xx) = 255;
			//以该点为中心再进行跟踪  
			TraceEdge(yy, xx, nThrLow, N, M);
		}
	}
}

vector<C_circle> CMycv::HoughCircl(Mat oimg, Mat img, float min_r, float max_r, float d_r, float min_angle, float circle_size, Scalar co)
{
	Mat out(oimg);
	vector<C_circle> circles;

	for (float r = min_r; r <= max_r; r += d_r)
	{
		cout << "正在处理" << r << "长的边，请等待" << endl;
		vector<C_circle> new_circles=HoughCircl_oneR(&img, r, min_angle, circle_size, co);
		int s = new_circles.size();
		cout << "检测出"<<s<<"个圆" << endl;
		for (int i = 0; i < s; i++)
		{
			circles.push_back(new_circles.at(i));
		}
	}
	return circles;
}

vector<C_circle> CMycv::HoughCircl_oneR(Mat* img, float r, float angle, float circle_size, Scalar co)
{
	int h = img->rows;
	int w = img->cols;

	Mat B(h, w, CV_32F,Scalar(0));
	vector<C_circle> circles;

	for (int i = 0; i < h; i++)
	{
		for (int j = 0; j < w; j++)
		{
			B.at<float>(i, j) = 0;
		}
	}

	int x0, y0;
	float t;	    
	for (int i = 0; i < h;i++)
	{
		for (int j = 0; j < w;j++)
		{
			if (img->at<uchar>(i,j) == 255)
			{
				for (int theta = 0; theta < 360; theta++)
				{
					t = (theta * C_PI) / 180; // 角度值0 ~ 2*PI  
						x0 = (int)(i - r * cos(t));
						y0 = (int)(j - r * sin(t));
					if (x0 < h && x0 > 0 && y0 < w && y0 > 0)
					{
						B.at<float>(x0, y0) = B.at<float>(x0, y0)+1;
					}
				}
			}
		}
	}
	for (int i = 0; i < h; i++)
	{
		for (int j = 0; j < w; j++)
		{
			if (B.at<float>(i,j)>=angle)
			{
				float x = i;
				float y = j;

				C_circle new_circle;
				new_circle.pos = Point2f(x, y);
				new_circle.r = r;
				new_circle.size = circle_size;
				new_circle.wight = B.at<float>(i, j);

				circles.push_back(new_circle);
			}
		}
	}
	return circles;
}

void CMycv::circle(Mat* img, Point sp, float r, float size, Scalar co)
{
	int h = img->rows;
	int w = img->cols;
	float min_r = (r - size / 2)*(r - size / 2);
	float max_r = (r + size / 2)*(r + size / 2);
	for (int i = 0; i < h; i++)
	{
		for (int j = 0; j < w; j++)
		{
			float x = i-sp.x;
			float y = j-sp.y;
			float d = x*x + y*y;
			if (d>min_r && d<max_r)
			{
				img->at<Vec3b>(i, j)[0] = co[0];
				img->at<Vec3b>(i, j)[1] = co[1];
				img->at<Vec3b>(i, j)[2] = co[2];
			}
		}
	}
}