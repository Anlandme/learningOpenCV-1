#include<opencv2/opencv.hpp>
#include<iostream>
using namespace std;
int main_6_3() {
	IplImage* imgSrc = cvLoadImage("C:\\Users\\lejia\\Desktop\\pic\\Transform.png");
	IplImage* imgTemp = cvLoadImage("C:\\Users\\lejia\\Desktop\\pic\\tmp.png");
	CvSize sizeSrc = cvGetSize(imgSrc);
	CvSize sizeTemp = cvGetSize(imgTemp);
	CvSize sizeResult = cvSize(sizeSrc.width - sizeTemp.width + 1, sizeSrc.height - sizeTemp.height + 1);
	IplImage* imgResult = cvCreateImage(sizeResult, IPL_DEPTH_32F, 1);
	cvMatchTemplate(imgSrc, imgTemp, imgResult, CV_TM_CCORR_NORMED);
	cvShowImage("MatchResult",imgResult);
	double dMax = 0.0,dMin=0.0;
	CvPoint pmax,pmin;
	//�ҳ�ͼ���м���Сֵ����λ��
	cvMinMaxLoc(imgResult,&dMin,&dMax,&pmin,&pmax);
	cout << "max:" <<dMax<<" min:"<< dMin<< endl;
	CvPoint point2 = cvPoint(pmax.x + sizeTemp.width, pmax.y + sizeTemp.height); //�Խ�λ�� 
	cvRectangle(imgSrc, pmax, point2, cvScalar(255));
	cvShowImage("Find", imgSrc);
	cvWaitKey(0);
	return 0;
}

/*
	void cvMatchTemplate( 
						const CvArr* image, //����ͼƬ����ͨ����8-���ػ�32-���� ������ͼ��
						const CvArr* templ, //ģ��ͼƬ���ߴ粻�ܴ�������ͼƬ����������ͼƬ����ͬ����������
						CvArr* result,		//�ȽϽ����ӳ��ͼƬ����ͨ����32-���ظ�����
											  �ߴ���㣺���image�ߴ��� W��H��templ�ߴ��� w��h ���� result �ߴ�Ϊ(W-w+1����(H-h+1��
						int method			//ָ��ƥ�䷽�����뺯�� cvCalcBackProjectPatch ���ơ�
											  ������������ͼ�� image, ��ָ�������Ƚ� templ ��ͼ��ߴ�Ϊ w��h ���ص����򣬲����ȽϽ���浽 result �С�
											  ������ɱȽϺ�ͨ��ʹ��cvMinMaxLoc��ȫ����СֵCV_TM_SQDIFF*) 
											  �������ֵ (CV_TM_CCORR* and CV_TM_CCOEFF*)��
						);
	
*/