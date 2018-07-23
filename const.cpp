#include <iostream>
using namespace std;
//https://www.cnblogs.com/jiabei521/p/3335676.html
class A{
public:
	A(int i);
	void print();

	const int &r;
private:
	//2. 对于类中的const成员变量必须通过初始化列表进行初始化
	const int a;
	static const int b;
}；

const int A::b = 10;
A::A(int i):a(i),r(a){}

int main(){
	//1.常量
	const int num = 100;
	//error  num = 200;
	const int i,j = 10; //error i 未初始化

	return 0;
}

//3. const 对象默认为文件的局部变量
//file1.cc
int counter = 100; //define

//file2.cc
extern int counter;//user counter from file1.cc
++counter;//increments counter defined int file1.cc

//const 情况
//在全局作用域声明的const变量是定义该对象的文件的局部变量。此变量只存在于那个文件中，
//不能被其他文件访问。通过指定const变量为extern，就可以在整个程序中访问const对象。
//file1.cc
extern const int bufsize = 100;

//file2.cc
extern const int bufsize;
++bufsize //error

//4. const 引用是指向const对象的引用
const int ival = 1024;
const int &refVal = ival;
int &ref = ival;       //error  const引用是指向const对象的引用

//非const引用只能绑定到与该引用相同类型的对象。 const引用则可以绑定到不同但相关的类型的对象或绑定到右值。
int i = 42;
const int &r = 42;
const int &r2 = r+i;

double dval = 3.14;
//int tmp = fval;
//const int &ri = tmp;
const int &ri = dval;

//5. const 对象的动态宿主
//error
const int *pci_bad = new const int[100];

//ok
const int *pci_ok = new const int[100]();

//C++ 允许定义类类型的const数组，但该类类型必须提供默认构造函数：
const string *pcs = new string[100];
//这里便会调用string类的默认构造函数初始化数组元素。




