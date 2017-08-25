#include<stdio.h>
#include<opencv2/imgproc/imgproc.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/core/core.hpp>
using namespace cv;
int main_1_8_1()
{
	Mat image, res1, res2, res3;
	image = cv::imread("C:\\Users\\lejia\\Desktop\\pic\\1.png");
	if (!image.data)
		return -1;
	cv::imshow("Original", image);
	cv::flip(image, res1, 3);
	cv::imshow("Result1", res1);
	cv::flip(image, res2, 0);
	cv::imshow("Result2", res2);
	cv::flip(image, res3, -3);
	cv::imshow("Result3", res3);
	cv::waitKey(0);
	return 0;
}
/*
void flip(InputArray src, OutputArray dst, int flipCode);
flipCode ��תģʽ
flipCode==0		��ֱ��ת����X�ᷭת��
flipCode > 0	ˮƽ��ת����Y�ᷭת��
flipCode < 0	ˮƽ��ֱ��ת������X�ᷭת������Y�ᷭת���ȼ�����ת180�㣩
*/