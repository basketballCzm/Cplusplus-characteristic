#include <iostream>
#include <vector>
using namespace std;
//decltype和auto关键字一样，用于进行编译时刻的类型推导，不过他还是和auto有一定的区别，
//decltype的类型推导并不是像auto一样是从变量声明的初始化表达式获得变量类型，
//而是总是以一个普通表达式作为参数，返回该表达式的类型，而decltype并不会对表达式进行求值
/*
1. 如果e是一个没有带括号的标记符表达式或者类成员访问表达式，那么的decltype（e）就是e所命名的实体的类型。
此外，如果e是一个被重载的函数，则会导致编译错误。
2. 否则 ，假设e的类型是T，如果e是一个将亡值，那么decltype（e）为T&&
3. 否则，假设e的类型是T，如果e是一个左值，那么decltype（e）为T&。
4. 否则，假设e的类型是T，则decltype（e）为T。
*/
//在 c 语言中，通常来说有名字的变量就是左值(有名字，能够取到内存地址)(如上面例子中的 a, b)，
//而由运算操作(加减乘除，函数调用返回值等)所产生的中间结果(没有名字)就是右值，如上的 3 + 4， a + b 等。
//左值就是在程序中能够寻值的东西，右值就是没法取到它的地址的东西(不完全准确)能否获取内存地址。
//++x 与 x++ 假定x的定义为 int x=0;,那么前者是 lvalue，后者是rvalue。
//前者修改自身值，并返回自身；后者先创建一个临时对像，为其赋值，而后修改x的值，最后返回临时对像。

//区分表达式的左右值属性有一个简便方法：若可对表达式用 & 符取址，则为左值，否则为右值。
//比如&obj , &*ptr , &ptr[index] , &++x有效
//&1729 , &(x + y) , &std::string("meow"), &x++无效

//http://www.cnblogs.com/catch/p/3500678.html

//泛型编程中结合auto,用于追踪函数返回值的类型
template <typename _Tx, typename _Ty>
auto multiply(_Tx x, _Ty y)->decltype(x*y)
{
	return x*y;
}

struct {
	int d;
	double b;
}anos_s;

int main(){
	int i = 4;
	decltype(i) a;//a 为int类型

	//与using/typedef合用用于定义类型
	using size_t = decltype(sizeof(0));//sizeof(0)的返回值为size_t类型
	vector<int> vect;
	vect.push_back(1);
	vect.push_back(3);
	vect.push_back(5);
	using vectype = decltype(vect.begin());
	//typedef decltype(vect.begin()) vectype;
	for(vectype i = vect.begin(); i != vect.end(); i++){
		cout << *i << " ";
	}

	decltype(anos_s) s1;//重新利用匿名的结构体
	s1.d = 10;
	s1.b = 20;

	cout << multiply<int, double>(10,20) << endl;

	//decltype的四个运行规则
	int arr[5] = {0};
	int *ptr = arr;
	struct S{double d;}s;
	void Overloaded(int);
	void Overloaded(char);
	int&& RvalRef();
	const bool Func(int);

	//规则一
	decltype(arr) var1;//int 
	decltype(ptr) var2;//int*
	decltype(s.d) var3;//double
	//decltype(Overloaded) var4//重载函数编译错误

	//规则二 将亡值，推导为类型的右值引用
	decltype(RvalRef()) var5 = 1;

	//规则三 左值推导为类型引用
	decltype((i)) var6 = i;//int&
	decltype(true?i:i) var7 = i;//int& 条件表达式返回左值
	decltype(++i) var8 = i;//int& ++i返回i的左值
	decltype(arr[5]) var9 = i;// int& []操作返回左值
	decltype(*ptr) var10 = i;//int& *操作返回左值
	decltype("hello") var11 = "hello";//const char(&)[9]字符串字面常量为左值，且为const左值

	//规则四 以上都不是则推导为本类型
	decltype(1) var12;//const int
	decltype(Func(1)) var13=true;//const bool
	decltype(i++) var14 = i;//int i++ 返回右值

	//对于规则三不确定是左值或者右值时可以用表达式is_lvaule_reference
	//1 为左值。0为右值
	cout << is_lvalue_reference<decltype(++i)>::value << endl;//左值
	cout << is_lvalue_reference<decltype(RvalRef())>::value <<endl;//右值

	return 0;
}