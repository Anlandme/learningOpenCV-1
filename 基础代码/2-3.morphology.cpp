#include <opencv2/opencv.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <math.h>
#include <string.h>
#include <opencv/cv.h>
#include <stdio.h>
using namespace cv;
using namespace std;
int main_2_3()
{
	//����ԭͼ   
	Mat image = imread("C:\\Users\\lejia\\Desktop\\pic\\1.png");
	//��ʾԭͼ  
	imshow("��ԭͼ��", image);
	//��ȡ�Զ����  
	Mat element = getStructuringElement(MORPH_RECT, Size(15, 15));
	Mat out_erode,out_dilate;
	//���и�ʴ����  
	erode(image, out_erode, element);
	//�������Ͳ���  
	dilate(image, out_dilate, element);
	//��ʾЧ��ͼ  
	imshow("����ʴ������", out_erode);
	imshow("�����Ͳ�����", out_dilate);
	cvWaitKey(0);
	return 0;
}