#include <iostream>
#include <string>
using namespace std;

//相当于内容和计数的数据结构是相互分开
class _counter{
public:
	_counter(int u):count(u){}
	~_counter(){}
	int count;
};

template <class T>
class base_shared_ptr{
public:
	T* m_ptr;
	_counter* m_pcnt;
public:
	base_shared_ptr(){m_pcnt = NULL; m_ptr = NULL;}
	base_shared_ptr(T* p){
		if(NULL == p){
			m_ptr = NULL;
			m_pcnt = NULL;
			return;
		}
		m_ptr = p;
		m_pcnt = new _counter(1);
	}
	~base_shared_ptr(){desconstruct();}

	void desconstruct();
	bool is_empty();
	int get_count(){return m_pcnt->count;}
	T& operator*(){return *m_ptr;}
	T* operator->(){return m_ptr;}
	base_shared_ptr(base_shared_ptr& mp);
	base_shared_ptr& operator=(base_shared_ptr& mp);

};

template <class T>
bool base_shared_ptr<T>::is_empty(){
	if (NULL == m_ptr){
		return true;
	}
	return false;
}

template <class T>
base_shared_ptr<T>::base_shared_ptr(base_shared_ptr<T>& mp){
	m_ptr = mp.m_ptr;
	m_pcnt = mp.m_pcnt;
	//mp 为空赋值就不会计数
	if(mp.is_empty()){
		return;
	}
	m_pcnt->count++;
}

template <class T>
void base_shared_ptr<T>::desconstruct(){
	if(NULL == m_ptr){
		return;
	}
	m_pcnt->count--;
	if(0 == m_pcnt->count){
		delete m_pcnt;
		delete m_ptr;
	}

	m_ptr = NULL;
	m_pcnt = NULL;

}


//对一个shared_ptr对象进行赋值,需要对原来的对象进行处理
template <class T>
base_shared_ptr<T>& base_shared_ptr<T>::operator=(base_shared_ptr& mp){
	if(&mp == this){
		return *this;
	}

	desconstruct();
	m_ptr = mp.m_ptr;
	m_pcnt = mp.m_pcnt;

	if(mp.is_empty()){
		return *this;
	}
	m_pcnt->count++;
	return *this;
}

class myclass{
public:
	myclass(){cout << "create" << endl;}
	~myclass(){cout << "Delete" << endl;}
};

class newmyclass{
public:
	base_shared_ptr<newmyclass> parent;
	base_shared_ptr<newmyclass> child;
	string name;
	newmyclass(string name):name(name){cout << "new Create" << endl;}
	~newmyclass(){cout << "new delete " << name << endl;}
};

int main(){
	
	base_shared_ptr<myclass> ptr(new myclass());
	cout << ptr.get_count() << endl;
	base_shared_ptr<myclass> ptr1(ptr);
	base_shared_ptr<myclass> ptr2;
	ptr2 = ptr1;

	//当出现循环引用需要用到 weak_ptr
	
	base_shared_ptr<newmyclass> p1(new newmyclass("a"));
	base_shared_ptr<newmyclass> p2(new newmyclass("aaaa"));

	p1->child = p2;
	p2->parent = p1;
	return 0;
}