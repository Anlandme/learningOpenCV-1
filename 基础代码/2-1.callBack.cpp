//���ص�����
#include<iostream>
#include<time.h>
#include<windows.h>  
using namespace std;

void pressure(int i) {
	cout << endl << "���г������ˣ���ѹ��"<<i << endl;
}
void stop() {
	cout <<endl<< "���г�û�����ˣ���" << endl;
}
class Bicycle {
private:
	int press;
public:
	Bicycle(int _press) { press = _press; }
	void run(void(*pressEvent)(int), void(*stopEvent)()) {
		srand((unsigned)time(NULL));
		cout << "���г������ˣ�" << endl;
		while (true) {
			cout << "�ܡ�";
			Sleep(100);
			if (rand() % 8 == 0) {
				press = press - 1;
				pressEvent(press);
				if (press <= 0) {
					stopEvent();
					break;
				}
			}
		}
	}
};
int main_2_1() {
	Bicycle bike= Bicycle(5);
	bike.run(pressure, stop);
	return 0;
}
