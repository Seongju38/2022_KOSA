/*
A와 B를 입력 받은 후, A/B를 출력하세요.

객체화 및 함수화 처리하기
A와 B를 숫자로 받기
B=0 일 때 예외 문구 발생하기
예시 1)

입력 : 1 3
출력 : 0.333333
예시 2)

입력 : 4 5
출력 : 0.8
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
			cout << "0으로 나눌 수 없어요옹ㅜ^ㅜ" << endl;
			return 0; // Hmm...
		}
	}
};

class CalcHandler {

public:

	int MyCalc(Calc& obj, double a, double b) {
		cout << "두 수를 입력 해 주세요옹:) ";
		cin >> a >> b; // a, b는 입력받는 값이기 때문에 const 불가

		if (cin.fail() != 0) {
			cout << "우메~ 문자가 들어왔어요오ㅜ 문자는 연산할 수 없어요오" << endl;
			return 0;
		}
		cin.clear(); // 문자가 들어왔을 때, cin.fail()의 값 비우기
		cin.ignore(); // 버퍼 안에 있는 내용 무시하기

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