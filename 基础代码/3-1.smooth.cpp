#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;

int pic_width = 250;
int pic_height = 250;
Mat pic;
Mat tmp_blur;
Mat tmp_gaussianblur;

int sigma = 1;
int kernel = 1;
void valuechange(int, void*)
{
	//�˴�С��Ϊż��
	kernel = kernel & 1 ? kernel : kernel + 1;
	//��ֵ�˲�����������ͼ�����ͼ���˴�С
	blur(pic, tmp_blur, Size(kernel, kernel), Point(-1, -1), BORDER_DEFAULT);
	//��˹ģ��
	GaussianBlur(pic, tmp_gaussianblur, Size(kernel, kernel), (double)sigma / 10, (double)sigma / 100, BORDER_DEFAULT);//��˹�˲�����
	imshow("ԭͼ", pic);
	imshow("ģ������", tmp_blur);
	imshow("��˹ģ��", tmp_gaussianblur);
}
int main_3_1_()
{
	pic = imread("C:\\Users\\lejia\\Desktop\\pic\\1.png");
	imshow("ԭͼ", pic);
	createTrackbar("�˴�С", "ԭͼ", &kernel, 100, valuechange);
	createTrackbar("��˹sigma��", "ԭͼ", &sigma, 100, valuechange);
	valuechange(NULL,NULL);
	waitKey(0);
	return 0;
}