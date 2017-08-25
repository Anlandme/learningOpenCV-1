#include<iostream>
#include<opencv2/opencv.hpp>
#include <opencv2\imgproc\imgproc.hpp>  
using namespace cv;
using namespace std;
int main_5_1()
{
	//��������
	CvPoint2D32f srcTri[3], dstTri[3];
	//����ָ��
	CvMat* warp_mat = cvCreateMat(2, 3, CV_32FC1);
	CvMat* rot_mat = cvCreateMat(2, 3, CV_32FC1);
	//�������ʾͼ��
	IplImage *src;
	src = cvLoadImage("C:\\Users\\lejia\\Desktop\\pic\\1.png", CV_LOAD_IMAGE_UNCHANGED);
	cvNamedWindow("ԭͼ", CV_WINDOW_AUTOSIZE);
	cvShowImage("ԭͼ", src);

	IplImage *dst = cvCreateImage(cvGetSize(src), IPL_DEPTH_8U, 1);
	dst = cvCloneImage(src);

	dst->origin = src->origin;
	cvZero(dst);
	//����1��
	//�ֱ�ָ��Դ�����Ŀ������3����
	srcTri[0].x = 0;
	srcTri[0].y = 0;
	srcTri[1].x = src->width;
	srcTri[1].y = 0;
	srcTri[2].x = 0;
	srcTri[2].y = src->height;

	dstTri[0].x = 10;
	dstTri[0].y = 10;
	dstTri[1].x = 200;
	dstTri[1].y = 50;
	dstTri[2].x = 60;
	dstTri[2].y =250;
	//ʹ�ö���ĵ����������������
	cvGetAffineTransform(srcTri, dstTri, warp_mat);
	//cvPerspectiveTransform(srcTri, dstTri, warp_mat);
	//�Ծ�����з���任
	cvWarpAffine(src, dst, warp_mat);
	cvNamedWindow("����ͼ1", CV_WINDOW_AUTOSIZE);
	cvShowImage("����ͼ1", dst);
	cvSaveImage("C:\\Users\\lejia\\Desktop\\pic\\Transform.png", dst);
	//����2��
	CvPoint2D32f center = cvPoint2D32f(src->width / 2, src->height / 3);//�������ĵ�
	double angle = -50.0;//��ת�Ƕ�
	double scale = 0.5;//����������������Ч���൱����ת180��
	//����õ�������ת���ű任�ķ����������
	cv2DRotationMatrix(center, angle, scale, rot_mat);
	//�Ծ�����з���任
	cvWarpAffine(src, dst, rot_mat);
	Mat t;  //�任����  
	cvNamedWindow("����ͼ2", CV_WINDOW_AUTOSIZE);
	cvShowImage("����ͼ2", dst);

	cvWaitKey();
	cvReleaseImage(&src);
	cvReleaseImage(&dst);
	cvDestroyWindow("ԭͼ");
	cvDestroyWindow("����ͼ1");
	cvDestroyWindow("����ͼ2");
	cvReleaseMat(&rot_mat);
	cvReleaseMat(&warp_mat);
	return 0;


}