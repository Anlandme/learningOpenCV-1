/************************************************************************/
/*
OpenCVͼ������ʹ�õĺ����ǣ�resize
void resize(InputArray src, OutputArray dst, Size dsize, double fx=0, double fy=0, int interpolation=INTER_LINEAR )
�������壺
InputArray src     -ԭͼ��
OutputArray dst    -���ͼ��
Size dsize         -Ŀ��ͼ��Ĵ�С
double fx=0        -��x���ϵ����ű���
double fy=0        -��y���ϵ����ű���
int interpolation  -��ֵ��ʽ�����������ַ�ʽ

INTER_NN      -����ڲ�ֵ
INTER_LINEAR  -˫���Բ�ֵ (ȱʡʹ��)
INTER_AREA    -ʹ�����ع�ϵ�ز�������ͼ����Сʱ�򣬸÷������Ա��Ⲩ�Ƴ��֡���ͼ��Ŵ�ʱ�������� INTER_NN ������
INTER_CUBIC   -������ֵ��

˵����dsize��fx��fy���벻��ͬʱΪ��
*/
/************************************************************************/
#include <opencv2\opencv.hpp>  
#include <opencv2\imgproc\imgproc.hpp>  

using namespace cv;

int main()
{
	//����ͼ��  
	Mat srcImage = imread("C:\\Users\\lejia\\Desktop\\pic\\1.png");
	Mat temImage, dstImage1, dstImage2;
	temImage = srcImage;

	//��ʾԭͼ  
	imshow("ԭͼ", srcImage);

	//�ߴ����  
	resize(temImage, dstImage1, Size(), 0.5, 1.3, INTER_LINEAR);
	resize(temImage, dstImage2, Size(temImage.cols * 2, temImage.rows * 2), 0, 0, INTER_LINEAR);

	imshow("��С", dstImage1);
	imshow("�Ŵ�", dstImage2);
	waitKey();
	return 0;

}