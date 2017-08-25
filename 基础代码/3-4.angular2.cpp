#include <opencv2/opencv.hpp>  
#include <opencv2/imgproc/imgproc.hpp> 
#include<iostream>
using namespace std;
using namespace cv;

void drawCornerOnImage(Mat& image, const Mat&binary)
{
	Mat_<uchar>::const_iterator it = binary.begin<uchar>();
	Mat_<uchar>::const_iterator itd = binary.end<uchar>();
	for (int i = 0; it != itd; it++, i++)
	{
		if (*it)
			circle(image, Point(i%image.cols, i / image.cols), 10, Scalar(0, 255, 0), 1);
	}
}
int main_3_4()
{
	//ʹ�ûҶ�ͼ���� Mat image = imread("C:\\Users\\lejia\\Desktop\\opencv\\pic\\10.png",0);
	Mat image = imread("C:\\Users\\lejia\\Desktop\\pic\\1.png");
	Mat gray;
	cvtColor(image, gray, CV_BGR2GRAY);

	//�ҳ��ǵ�
	Mat cornerStrength;
	cornerHarris(gray, cornerStrength, 3, 3, 0.01);

	double maxStrength;
	double minStrength;
	//�ҵ��ǵ�ͼ���е������Сֵ
	minMaxLoc(cornerStrength, &minStrength, &maxStrength);

	Mat dilated;
	Mat locaMax;

	// cornerstrength���ʹ��������dilated
	dilate(cornerStrength, dilated, Mat());

	//��������ͼ���ж�Ӧ����ͬ�Ķ�ֵͼ��
	compare(cornerStrength, dilated, locaMax, CMP_EQ);

	Mat cornerMap;
	double qualityLevel = 0.01;
	double th = qualityLevel*maxStrength;
	//��ֵ����:qualitylevel*ͼ���е����ֵ���ǵ�������ɫ��
	threshold(cornerStrength, cornerMap, th, 255, THRESH_BINARY);
	cornerMap.convertTo(cornerMap, CV_8U);

	// ����λ���㣬ʹÿ���ǵ㶼ֻռ��һ����
	bitwise_and(cornerMap, locaMax, cornerMap);
	imshow("��ֵͼ", cornerMap);
	drawCornerOnImage(image, cornerMap);
	namedWindow("result");
	imshow("result", image);
	waitKey();

	return 0;
}