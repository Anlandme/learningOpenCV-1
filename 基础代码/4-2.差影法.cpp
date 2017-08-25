#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/core/core.hpp>
#include<iostream>
using namespace std;

#define threshold_diff 20 //���ü�֡���ֵ

using namespace cv;
using namespace std;

int main_4_2()
{
	Mat src1, src2, img_dst, gray1, gray2, gray_diff;
	bool stop = false;
	int count = 0;
	VideoCapture capture;
	if (!capture.open(0)) {
		cout << "������ͷʧ�ܣ�" << endl;
		return -1;
	}
	while (!stop)
	{
		count++;
		if (count %= 10) {
			//���¶Ա�ͼ
			capture >> src1;
			cvtColor(src1, gray1, CV_BGR2GRAY);
			waitKey(50);
		}
		//��ͼ
		capture >> src2;
		cvtColor(src2, gray2, CV_BGR2GRAY);
		imshow("video_src", src2);
		//����ͼƬ�������㣬��ͨ������ͬ
		subtract(gray1, gray2, gray_diff);
		for (int i = 0; i < gray_diff.rows; i++)
			for (int j = 0; j < gray_diff.cols; j++) {
				//����ģ�����һ��Ҫ��unsigned char�������һֱ����
				if (abs(gray_diff.at<unsigned char>(i, j)) >= threshold_diff)
					gray_diff.at<unsigned char>(i, j) = 255;
				else gray_diff.at<unsigned char>(i, j) = 0;
			}
		imshow("diff", gray_diff);

		char c = (char)waitKey(20);
		if (c == 27)
			stop = true;
	}
	return 0;
}