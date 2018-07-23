#include <iostream>
class A;
class B;

/*
1. 友元函数
2. 友元类
*/

class A{
public:
	//友元类
	friend class B;
	A(int num):m_num(num){}
	~A(){}
	//前项声明不能直接实例化一个对象,在这里只能使用引用，并且在这里定义应该放到后面
	void show(B& num);
	//这个友元函数会因为前项声明不能导致类域的实例化
	//friend void B::show1(A& num);
private:
	int m_num;
};

class B{
public:
	//friend class A;
	B(int num):m_num(num){}
	~B(){}
	void show1(A& num);
	friend void A::show(B& num);
private:
	int m_num;
};

inline void B::show1(A& num){
	std::cout << "hello class B:" << num.m_num << std::endl;
}

inline void A::show(B& num){
	std::cout << "hello class A:" << num.m_num <<std::endl;
}

int main()
{
	A tmp(10);
	B tmp1(20);
	tmp.show(tmp1);
	tmp1.show1(tmp);
	return 0;
}