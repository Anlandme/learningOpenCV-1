//#include<opencv2/opencv.hpp>
//using namespace cv;
//using namespace std;
//int main_3_2()
//{
//	Mat a = imread("C:\\Users\\lejia\\Desktop\\pic\\1.png");
//	imshow("ԭͼ", a);
//	cvtColor(a, a, CV_RGB2GRAY);     //תΪ�Ҷ�ͼ
//	Mat ax, ay;
//	Mat axx, ayy;
//	Sobel(a, ax, CV_16S, 1, 0, -1);
//	Sobel(a, ay, CV_16S, 0, 1, -1);
//	convertScaleAbs(ax, axx);      //��CV_16SתΪCV_8U
//	convertScaleAbs(ay, ayy);
//	addWeighted(axx, 0.5, ayy, 0.5, 0, a);     //����ͼ���
//	imshow("Ч��ͼ1", axx);
//	imshow("Ч��ͼ2", ayy);
//	imshow("Ч��ͼ3", a);
//	cvWaitKey(10000);
//	return 1;
//}

#include <opencv2/opencv.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc/imgproc.hpp>
using namespace cv;
Mat srcImage;
Mat srcImage1;
int value = 3;

Mat dstImage, edge, grayImage;

void handleEdge(int, void*)
{
	value = (value <1 ? 1 : value);
	//3x3�ں�������(��ֵ�˲�)
	blur(grayImage, edge, Size(value, value));
	imshow("edge",edge);
	//Canny����
	//��OpenCV2�п��ã�OpenCV3����ʧЧ
	//�߽׵�canny�÷�:
	//ת�Ҷ�ͼ,����,canny,���õ��ı�Ե��Ϊ���룬����ԭͼ��Ч��ͼ�ϣ��õ���ɫ�ı�Եͼ
	Canny(edge, edge, 3, 9, 3);
	dstImage = Scalar::all(255);
	//ʹ�ñ�Եͼ��Ϊ������п�������ֻ����edge�Ĺ켣������λ�ò�����
	srcImage1.copyTo(dstImage, edge);
	imshow("Ч��ͼ", dstImage);
}
int main_3_2()
{
	//����ԭʼͼ  
	srcImage = imread("C:\\Users\\lejia\\Desktop\\pic\\1.png");
	srcImage1 = srcImage.clone();
	//��ԭͼ��ת��Ϊ�Ҷ�ͼ��
	cvtColor(srcImage1, grayImage, COLOR_BGR2GRAY);
	dstImage.create(srcImage1.size(), srcImage1.type());
	//��ʾԭʼͼ 
	imshow("ԭͼ", srcImage);
	namedWindow("Ч��ͼ");
	createTrackbar("kernel Size:", "Ч��ͼ", &value, 100, handleEdge);
	waitKey(0);
	return 0;
}