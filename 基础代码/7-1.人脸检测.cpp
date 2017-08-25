#include "opencv2/objdetect/objdetect.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"

#include <iostream>
#include<time.h>
#include <stdio.h>

using namespace std;
using namespace cv;

String cascadeName = "C:\\Users\\lejia\\Desktop\\opencvѧϰ\\code\\haarcascade\\haarcascade_frontalface_alt2.xml";
String nestedCascadeName = "C:\\Users\\lejia\\Desktop\\opencvѧϰ\\code\\haarcascade\\haarcascade_eye_tree_eyeglasses.xml";
String cascadeName2 = "C:\\Users\\lejia\\Desktop\\opencvѧϰ\\code\\haarcascade\\aGest.xml";

CascadeClassifier cascade, nestedCascade;

void detectAndDraw(Mat& img, double scale);
void detectAndDrawInner(int scale, vector<Rect>::const_iterator &r, Mat &img, Mat &smallImg);
int main_7_1() {

	Mat frameCopy, image;
	Mat frame;
	double scale = 1;

	VideoCapture capture;
	if (!capture.open(0)) {
		cout << "������ͷʧ�ܣ�" << endl;
		return -1;
	}
	//ѡ�񲢼�������Դ
	if (true) {
		cascade.load(cascadeName);
		nestedCascade.load(nestedCascadeName);
	}
	else {
		cascade.load(cascadeName2);
		nestedCascade.load(cascadeName2);
	}
	while (true) {
		capture >> frame;
		detectAndDraw(frame, scale);
		if (waitKey(10) == 'q')
			break;
	}
	capture.release();
	cvDestroyWindow("result");
	return 0;
}
//����
void detectAndDraw(Mat& img, double scale) {
	vector<Rect> faces;
	Mat gray, smallImg(cvRound(img.rows / scale), cvRound(img.cols / scale), CV_8UC1);
	cvtColor(img, gray, CV_BGR2GRAY);
	resize(gray, smallImg, smallImg.size(), 0, 0, INTER_LINEAR);
	//ֱ��ͼ��һ��
	//imshow("��һ��ǰ",smallImg);
	//equalizeHist(smallImg, smallImg);
	//imshow("��һ����", smallImg);
	//waitKey(0);

	cascade.detectMultiScale(smallImg, faces,
		1.1, 2, 0
		| CV_HAAR_FIND_BIGGEST_OBJECT
		//|CV_HAAR_DO_ROUGH_SEARCH
		| CV_HAAR_SCALE_IMAGE,
		Size(30, 30)
	);
	for (vector<Rect>::const_iterator r = faces.begin(); r != faces.end(); r++) {
		detectAndDrawInner(scale, r, img, smallImg);
	}
	cv::imshow("result", img);
}
//�����
void detectAndDrawInner(int scale, vector<Rect>::const_iterator &r, Mat &img, Mat &smallImg) {
	Mat smallImgROI;
	vector<Rect> nestedObjects;
	Point center;
	srand((unsigned int)time(NULL));
	Scalar color(rand() & 255, rand() & 255, rand() & 255);
	int radius;
	center.x = cvRound((r->x + r->width*0.5)*scale);
	center.y = cvRound((r->y + r->height*0.5)*scale);
	radius = cvRound((r->width + r->height)*0.25*scale);
	rectangle(img, Point(center.x + radius, center.y + radius), Point(center.x - radius, center.y - radius), color, 1, 8, 0);
	if (nestedCascade.empty())
		return;
	smallImgROI = smallImg(*r);
	nestedCascade.detectMultiScale(smallImgROI, nestedObjects,
		1.1, 2, 0
		//|CV_HAAR_FIND_BIGGEST_OBJECT
		//|CV_HAAR_DO_ROUGH_SEARCH
		//|CV_HAAR_DO_CANNY_PRUNING
		| CV_HAAR_SCALE_IMAGE
		,
		Size(30, 30));
	for (vector<Rect>::const_iterator nr = nestedObjects.begin(); nr != nestedObjects.end(); nr++) {
		center.x = cvRound((r->x + nr->x + nr->width*0.5)*scale);
		center.y = cvRound((r->y + nr->y + nr->height*0.5)*scale);
		radius = cvRound((nr->width + nr->height)*0.25*scale);
		circle(img, center, radius, color, 2, 8, 0);
	}
}

/*
1��bool load( const String& filename );		//����ѵ���õ�xml�ļ�

2��void detectMultiScale(
InputArray image,						//�����ͼƬ
CV_OUT std::vector<Rect>& objects,	//������������ھ������򼯺ϣ��ɶ����
double scaleFactor = 1.1,				//��ʾ��ǰ��������̵�ɨ���У��������ڵı���ϵ����
Ĭ��Ϊ1.1��ÿ������������������10%;
int minNeighbors = 3,					//��ʾ���ɼ��Ŀ������ھ��ε���С����(Ĭ��Ϊ3��)
�����ɼ��Ŀ���С���εĸ�����С�� min_neighbors - 1 ���ᱻ�ų�
���min_neighbors Ϊ 0, ���������κβ����ͷ������еı����ѡ���ο�
int flags = 0,						//ʹ��Ĭ��ֵ������CV_HAAR_DO_CANNY_PRUNING���������Ϊ����
��ô��������ʹ��Canny��Ե������ų���Ե�������ٵ�������Щ������ܲ���Ŀ����������
Size minSize = Size(),				//�ҵ���Ŀ����С�ߴ磬�����������
Size maxSize = Size()
);				//�ҵ���Ŀ�����ߴ磬�����������
*/
