#include <iostream>
using namespace std;

class A;
class B;

class A
{
public:
	A(int num):m_num(num){}
	~A(){}
	friend void show(A& a, B& b);
private:
	int m_num;
};

class B
{
public:
	B(int num):m_num(num){}
	~B(){}
	friend void show(A& a, B& b);
private:
	int m_num;
};

void show(A& a, B& b)
{
	std::cout << "this is a show class: " << a.m_num << "   " << b.m_num << std::endl;
}

int main()
{
	A tmp(10);
	B tmp1(20);
	show(tmp, tmp1);
	return 0;
}