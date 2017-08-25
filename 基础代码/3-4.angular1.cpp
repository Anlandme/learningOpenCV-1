#include <opencv2/opencv.hpp>  
#include <opencv2/imgproc/imgproc.hpp>  
using namespace cv;

int BlockSize = 2;
int kSize = 3;
int k = 1;//��ʼΪ0.01
Mat SrcImage, cornerStrength;
void trackevent(int, void *)
{
	//��harris�㷨��ȡ�ǵ�
	cornerHarris(SrcImage, cornerStrength, BlockSize<=0?1:BlockSize, kSize, (double)k / 100);
	
	//�ԻҶ�ͼ������ֵ�������õ���ֵͼ����ʾ  
	Mat harrisCorner;
	threshold(cornerStrength, harrisCorner, 0.00001, 255, THRESH_BINARY);
	imshow("Ч��ͼ", harrisCorner);
}
int main_3_4_1()
{
	//�ԻҶ�ģʽ����ͼ����ʾ
	SrcImage = imread("C:\\Users\\lejia\\Desktop\\pic\\1.png", 0);
	imshow("ԭʼͼ", SrcImage);
	namedWindow("Ч��ͼ");
	createTrackbar("blockSize:", "Ч��ͼ", &BlockSize, 100, trackevent);
	createTrackbar("kSize:", "Ч��ͼ", &kSize, 100, trackevent);
	createTrackbar("k:", "Ч��ͼ", &k, 100, trackevent);
	waitKey(0);
	return 0;
}