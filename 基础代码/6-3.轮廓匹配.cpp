#include<opencv2\opencv.hpp>
int main()
{
	IplImage *mode = cvLoadImage("C:\\Users\\lejia\\Desktop\\pic\\1-tmp.png",0);
	IplImage *test = cvLoadImage("C:\\Users\\lejia\\Desktop\\pic\\1.png",0);
	
	CvMemStorage *mode_mems = cvCreateMemStorage();
	CvSeq *mode_seqs;
	CvMemStorage *test_mems = cvCreateMemStorage();
	CvSeq *test_seqs;

	cvFindContours(mode, mode_mems,
		&mode_seqs, sizeof(CvContour), CV_RETR_TREE);

	cvFindContours(test, test_mems,
		&test_seqs, sizeof(CvContour), CV_RETR_TREE);

	double matching = cvMatchShapes(test, mode, 3);
	printf("ͼ��ıȽϽ����%f\n", matching);
	matching = cvMatchShapes(test_seqs, mode_seqs, 3);
	printf("�����ıȽϽ����%f\n", matching);

	cvReleaseImage(&mode);
	cvReleaseImage(&test);
	system("pause");
	return 1;
}


/*
	MatchShapes �Ƚ�������״
	����ԭ�ͣ�
	double cvMatchShapes( 
						const void* object1,  //��һ��������Ҷ�ͼ��
						const void* object2,  //�ڶ���������Ҷ�ͼ��
						int method,			  //�ȽϷ�����	 
												CV_CONTOUR_MATCH_I1, CV_CONTOURS_MATCH_I2 or CV_CONTOURS_MATCH_I3.��
												����ʵ�ַ���ȫ��ʹ�� Hu �� (�� cvGetHuMoments)
						double parameter=0	  //�ȽϷ����Ĳ��� (Ŀǰ����)����������
						);
	�Աȵ�����ͼƬ����λ�ú�����һ����ͬһ��ͼƬ�ԱȽ��Ϊ0��
*/