#include <opencv2/opencv.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv/cv.h>
#include <stdio.h>
using namespace cv;
using namespace std;
int main()
{
	//����ԭʼͼ    
	Mat image = imread("C:\\Users\\lejia\\Desktop\\pic\\1.png");
	//��ʾԭʼͼ   
	imshow("��ԭʼͼ��", image);
	//�����  
	Mat element = getStructuringElement(MORPH_RECT, Size(15, 15));
	//������̬ѧ����  
	Mat open, close;
	//������
	morphologyEx(image, open, MORPH_OPEN, element);
	//������
	morphologyEx(image, close, MORPH_CLOSE, element);
	//��ʾЧ��ͼ   
	imshow("�������㡿", open);
	imshow("�������㡿", close);
	waitKey(0);

	return 0;
}
