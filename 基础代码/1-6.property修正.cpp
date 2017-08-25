#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <math.h>
#include <string.h>
#include <opencv/cv.h>
#include<iostream>
#include <stdio.h>
using namespace cv;
using namespace std;

Mat origin;
Mat change;
int alpha = 1;
float beta = 3;
const char *InputTitle = "ԭͼ";
const char *OutputTitle = "��ͼ";

void on_trackbar(int pos)
{
	alpha = pos;
	for (int i = 0; i<origin.rows; i++)
		for (int j = 0; j<origin.cols; j++)
		{
			//saturate_castΪ�������,
			change.at<Vec3b>(i, j)[0] = saturate_cast<uchar>(alpha*origin.at<Vec3b>(i, j)[0] + beta);
			change.at<Vec3b>(i, j)[1] = saturate_cast<uchar>(alpha*origin.at<Vec3b>(i, j)[1] + beta);
			change.at<Vec3b>(i, j)[2] = saturate_cast<uchar>(alpha*origin.at<Vec3b>(i, j)[2] + beta);
		}
	imshow(OutputTitle, change);
	cout << "����:" << pos << endl;
}

int main(int argc, char** argv) {
	cvNamedWindow(InputTitle, CV_WINDOW_AUTOSIZE);
	cvNamedWindow(OutputTitle, CV_WINDOW_AUTOSIZE);
	origin = imread("C:\\Users\\lejia\\Desktop\\pic\\1.png");
	change = imread("C:\\Users\\lejia\\Desktop\\pic\\1.png");;
	// ������  
	int nThreshold = 1;
	cvCreateTrackbar("����:", OutputTitle, &nThreshold, 10, on_trackbar);
	imshow(InputTitle, origin);
	imshow(OutputTitle, change);
	cvWaitKey(0);

	origin.release();
	change.release();
	cvDestroyWindow(InputTitle);
	cvDestroyWindow(OutputTitle);
	return 0;
}