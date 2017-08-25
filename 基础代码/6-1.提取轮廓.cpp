#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;
int main_6_1(){
	Mat src = imread("C:\\Users\\lejia\\Desktop\\pic\\lines.png",0);
	imshow("�Ҷ�ͼ", src);
	//������ֵ������
	threshold(src, src, 100, 255, THRESH_BINARY);
	//���Դ�������ļ���
	vector<vector<Point>> contours;
	findContours(src, contours, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_NONE);
	Mat crop;
	for (vector<vector<Point>>::iterator it = contours.begin(); it != contours.end(); it++) {
		//�ӵ㼯�л�ȡ�������о���
		Rect rect = boundingRect(*it);
		//�ô�����С������
		if (rect.width<20 || rect.height<20)
			continue;
		crop = src(Range(rect.y, rect.y + rect.height), Range(rect.x, rect.x + rect.width));
		//�������������������
		char str[15];
		sprintf(str,"���%f",contourArea(*it));
		cout << str << endl;
		
		sprintf(str, "�ܳ� closed��%f", arcLength(*it,true));
		cout << str << endl;
		sprintf(str, "�ܳ���%f", arcLength(*it, false));
		cout << str << endl;
		imshow("����", crop);
		cvWaitKey(0);
	}
	//����ȫ������
	Mat contoursImage(src.rows, src.cols, CV_8UC3, Scalar(255,255,255));
	for (int i = 0, srand((unsigned)time(NULL)); i < contours.size(); i++) {
		//�ú�����i���Ϊ-1�򻭳�ȫ������������ʱ����Ҫ���forѭ��
		drawContours(contoursImage, contours, i, Scalar(rand() & 255, rand() & 255, rand() & 255), 2);
	}
	imshow("����", contoursImage);
	waitKey(0);
	src.release();
	cvDestroyAllWindows();
	return 0;
}
/*
	1��findContours ����ԭ��Ϊ��
	void findContours(
					  InputOutputArray image,			//����һ��2ֵ�����ĵ�ͨ��ͼ�񣨱�Ե��ȡ����ֵ����
					  OutputArrayOfArrays contours,		//��⵽���������ϣ�ÿ���������Ǹ��㼯��
														  vector<vector<Point>> contours
					  OutputArray hierarchy,			//���ز㼶���ϣ��ͷ�������������ͬ��
														  ÿ������contours[ i ]��Ӧ4��Ԫ�أ�
														  hierarchy[ i ][ 0 ] ~hierarchy[ i ][ 3 ]
														  �ֱ��ʾ��һ��������ǰһ������������������Ƕ������������ţ����û�ж�Ӧ���ֵ����Ϊ������
														 
					  int mode,							 //mode��ʾ�����ļ���ģʽ:
														   CV_RETR_EXTERNAL	��ʾֻ���������
														   CV_RETR_LIST		���������������ȼ���ϵ
														   CV_RETR_CCOMP	���������ȼ��������������һ��Ϊ��߽磬�����һ��Ϊ�ڿ׵ı߽���Ϣ������ڿ��ڻ���һ����ͨ���壬�������ı߽�Ҳ�ڶ��㡣
														   CV_RETR_TREE		����һ���ȼ����ṹ������������ο�contours.c���demo
					  int method,						 //methodΪ�����Ľ��ư취:
														   CV_CHAIN_APPROX_NONE		�洢���е������㣬���ڵ������������λ�ò����1����max��abs��x1-x2����abs��y2-y1����==1
														   CV_CHAIN_APPROX_SIMPLE	ѹ��ˮƽ���򣬴�ֱ���򣬶Խ��߷����Ԫ�أ�ֻ�����÷�����յ����꣬����һ����������ֻ��4����������������Ϣ
														   CV_CHAIN_APPROX_TC89_L1��CV_CHAIN_APPROX_TC89_KCOSʹ��teh-Chinl chain �����㷨		 
					  Point offset=Point()				 //offset��ʾ�����������ƫ����:
														   ��������Ϊ����ֵ����ROIͼ�����ҳ�����������Ҫ������ͼ���н��з���ʱ������������Ǻ����õġ�
					  );
	tip: findContours���������Ϣ���ܹ��ڸ��Ӳ�ƽ����������approxPolyDP�����Ըö�����������ʵ����ơ�
	
	2��contourArea �������Եõ���ǰ������������Ĵ�С������������ɸѡ��
	
	3��drawContours �������ڽ�һ����������������ԭ�ͣ�
	void drawContours( InputOutputArray image,			//������ͼ��						
					   InputArrayOfArrays contours,		//�������ϣ�ֻ�ử�������е�һ������Ԫ�أ���ȫ����
                       int contourIdx,					//ָ�������ڼ�����������
					   const Scalar& color,				//������ɫ
                       int thickness = 1,				//�����߿�Ϊ��ֵ��CV_FILLED������������ڲ���
					   int lineType = LINE_8,			//�ߵ����ͣ������ߣ�ʵ�ߣ��޾��������
                       InputArray hierarchy = noArray(),//�����ṹ��Ϣ
                       int maxLevel = INT_MAX,			
					   Point offset = Point() 
					  );
	4��convexHull ���������������ʺ������ļ�⣬ʹ�øú������ڼ������ṹ����ȡ������͹����ĵ㼯

	5��boundingRect �õ��������������Σ����ŵľ��Σ�

	6��minAreaRect �õ���ת���������Σ�����ֵΪRotatedRect

	7��minEnclosingCircle �õ������������Բ

	8��fitEllipse �õ��������������Բ������ֵҲ��RotatedRect����ellipse����������Ӧ����Բ

	9��moments ���ݶ���ε�������Ϣ�õ�����εĶ�׾أ��������Եõ�����κ͹�դ��״��3�����ڵ����оأ������б���m00��m10��m01��m20��m11��m02��m30��m21��m12��m03���������ε�����Ϊ x = m10 / m00��y = m01 / m00��

	10��pointPolygonTest ���ĳ���������ľ��룬����ֵΪ�õ������������߽�ľ��루��ֵΪ�������ڲ�����ֵΪ�������ⲿ��0��ʾ�ڱ߽��ϣ�

*/