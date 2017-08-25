#include<stdio.h>  
#include<cv.h>  
#include<highgui.h>  
int main()
{
	IplImage* image = cvLoadImage("C:\\Users\\lejia\\Desktop\\pic\\lines.png", 0); //����ͼ��  
	IplImage* dst = cvCreateImage(cvGetSize(image), 8, 3);
	cvCanny(image, image, 100, 255);//���ұ�Ե  
	cvCvtColor(image, dst, CV_GRAY2BGR);//ת������ɫ�ռ�  
	CvMemStorage* storage = cvCreateMemStorage(0); //����ֱ�ߵĴ洢�ռ�  
	CvSeq* seq = NULL;
	seq = cvHoughLines2(image, storage, CV_HOUGH_PROBABILISTIC, 1, CV_PI / 180, 50, 10, 15);//����任���ֱ��  

	for (int i = 0; i<seq->total; i++)
	{
		CvPoint* line = (CvPoint*)cvGetSeqElem(seq, i);
		cvLine(dst, line[0], line[1], CV_RGB(255, 0, 0), 1, 8, 0);
	}

	cvNamedWindow("��ԵͼƬ", 1);
	cvNamedWindow("�����", 1);
	cvShowImage("��ԵͼƬ", image);
	cvShowImage("�����", dst);
	cvWaitKey(0);

	//�ͷ��ڴ�ռ�  
	cvReleaseImage(&image);
	cvReleaseImage(&dst);
	cvDestroyWindow("cc");
	cvDestroyWindow("��ԵͼƬ");
	cvDestroyWindow("�����");
	cvReleaseMemStorage(&storage);
	return 0;
}