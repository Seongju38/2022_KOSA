/*
A�� B�� �Է� ���� ��, A/B�� ����ϼ���.

��üȭ �� �Լ�ȭ ó���ϱ�
A�� B�� ���ڷ� �ޱ�
B=0 �� �� ���� ���� �߻��ϱ�
���� 1)

�Է� : 1 3
��� : 0.333333
���� 2)

�Է� : 4 5
��� : 0.8
*/

#include <iostream>
#include <vector>
using namespace std;

class Calc {
public:
	virtual double calc(const double a, const double b) = 0;
};

class DivCalc : public Calc {
	virtual double calc(const double a, const double b) override{
		if (b != 0)
			return a / b;
		else {
			cout << "0���� ���� �� �����ˤ�^��" << endl;
			return 0; // Hmm...
		}
	}
};

class CalcHandler {

public:

	int MyCalc(Calc& obj, double a, double b) {
		cout << "�� ���� �Է� �� �ּ����:) ";
		cin >> a >> b; // a, b�� �Է¹޴� ���̱� ������ const �Ұ�

		if (cin.fail() != 0) {
			cout << "���~ ���ڰ� ���Ծ����� ���ڴ� ������ �� ������" << endl;
			return 0;
		}
		cin.clear(); // ���ڰ� ������ ��, cin.fail()�� �� ����
		cin.ignore(); // ���� �ȿ� �ִ� ���� �����ϱ�

		cout << obj.calc(a, b) << endl;
	}

};

bool InitCalc(CalcHandler* handler) {
	const double a = 0, b = 0;
	DivCalc divCalc;

	handler->MyCalc(divCalc, a, b);

	return true;
}

bool ExitCalc(CalcHandler* handler) {
	return true;
}

int main() {
	CalcHandler handler;

	InitCalc(&handler);
	ExitCalc(&handler);
}