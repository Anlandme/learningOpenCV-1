#include <opencv2\opencv.hpp>  
#include <opencv2\imgproc\imgproc.hpp>  
#include<iostream>
using namespace std;
using namespace cv;

//�����ȡ0-9����ÿ������ֻ����ȡһ��
int getSrcFlag() {
	//���ͼƬ��9��С����
	static bool flag[9] = { 0 };
	srand((unsigned)time(NULL));
	int f;
	do{
		f = rand() % 9;
	} while (flag[f]);
	flag[f] = true;
	return f;
}
//fromIndex:ԭͼ��ͼ��ţ�0-8����toIndex:Ŀ��ͼ��ͼ��ţ�0-8��
void getChildMat(Mat &src,Mat &dst,int fromIndex,int toIndex,int size) {
	if (fromIndex < 0 || fromIndex>8 ||toIndex<0 || toIndex>8)
		return;
	//�ֱ������ͼ��Ŀ��ͼ����ͼ���ڷ�Χ������Range����һ���ڴ湲�����ͼ��ԭ��
	//��Ŀ��ͼ����ͼ���и��ǣ��ڸ�����ͼ��ͬʱ��Ŀ��ԭͼ���޸ġ�
	Mat from = src(Range(size*(fromIndex % 3), size*(fromIndex % 3)+size), Range(size*(fromIndex / 3), size*(fromIndex / 3) + size));
	Mat to=dst(Range(size*(toIndex / 3), size*(toIndex / 3) + size), Range(size*(toIndex % 3), size*(toIndex % 3) + size));
	from.copyTo(to);
}
int main()
{
	//����ͼ��  
	Mat src = imread("C:\\Users\\lejia\\Desktop\\pic\\1.png");
	//����С����ߴ硣
	int size=(src.cols > src.rows ? src.rows : src.cols) / 3;
	resize(src,src, Size(size*3,size*3), 0, 0, INTER_LINEAR);
	Mat dst(src.size(), src.type());
	imshow("ԭͼ", src);
	for (int i = 0; i < 9; i++)
		getChildMat(src,dst,getSrcFlag(),i,size);
	imshow("�Ź�ͼ", dst);
	imwrite("C:\\Users\\lejia\\Desktop\\pic\\9path.png",dst);
	waitKey();
	return 0;
}