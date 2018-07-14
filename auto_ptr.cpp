#include <iostream>
using namespace std;
/*
auto_ptr 指针会出现所有权转移的现象，任何时候只能有一个智能指针指向那块内存区域
unique_ptr 只能有一个主人指针，可以用于STL容器
shared_ptr 可共享的指针
weak_ptr 弱引用类型的指针
*/

template <class T>
class base_auto_ptr{
private:
	T* m_ptr;
public:
	explicit base_auto_ptr(T* p = 0):m_ptr(p){}
	base_auto_ptr(base_auto_ptr& mp){
		// mp is unvalid
		m_ptr = mp.getPtr();
	}

	~base_auto_ptr(){delete m_ptr;}

	T& operator*(){return *m_ptr;}

	// this only is a pointer
	/*
	base_auto_ptr* operator->(){
		return this;
	}*/

	T* operator->(){return m_ptr;}

	base_auto_ptr& operator=(base_auto_ptr& mp);

	//return m_ptr and m_ptr is unvalid
	T* getPtr();

	T* getmPtr(){return m_ptr;}


};

template <class T>
bool operator!= (base_auto_ptr<T>& a, base_auto_ptr<T>& b){
	if(a.getmPtr() != b.getmPtr()){
		return true;
	}
	return false;
}

template <class T>
base_auto_ptr<T>& base_auto_ptr<T>::operator=(base_auto_ptr<T>& mp){
 	if (*this != mp){
		delete m_ptr;
		m_ptr = mp.getPtr();
	}

	return *this;
}

template <class T>
T* base_auto_ptr<T>::getPtr(){
	T* tmp = m_ptr;
	m_ptr = 0;
	return tmp;
}

struct Arwen{
	int age = 18;
	void show(){
		cout << "show time now!" << endl;
	}
};

int main(){
	base_auto_ptr<int> base(new int(88));
	cout << *base << endl;

	base_auto_ptr<int> base1(new int(44));
	cout << *base1 << endl;
	base1 = base;
	//cout << *base << endl; error
	
	base_auto_ptr<Arwen> base_A(new Arwen);
	base_A->show();
	cout << base_A->age << endl;


	return 0;
}