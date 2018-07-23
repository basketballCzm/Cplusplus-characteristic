#include <iostream>
#include <string>

//利用嵌套类和模板来实现一个队列
template <typename Item>
class QueueTP
{
private:
	enum {Q_SIZE=10};
	class Node{
	public:
		Item item;
		Node *next;
		Node(const Item &i):item(i),next(0){}
	};

	Node *front;
	Node *rear;
	int items;        //currency number of items in queue
	const int qsize;  //maximum number of items in queue
	QueueTP(const QueueTP &q):qsize(0){}
	QueueTP& operator=(const QueueTP &q){return *this;}
public:
	QueueTP(int qs = Q_SIZE);
	~QueueTP();
	bool isempty() const{
		return items == 0;
	}
	bool isfull() const{
		return items == qsize;
	}
	int queuecount() const{
		return items;
	}
	bool enqueue(const Item &item);
	bool dequeue(Item &item);
};

template <typename Item>
QueueTP<Item>::QueueTP(int qs):qsize(qs){
	//将指针初始化为零，可以避免因为C++版本不同而导致的NULL和nullptr的差别
	front = rear = 0;
	items = 0;
}

template <typename Item>
QueueTP<Item>::~QueueTP(){
	Node *temp = 0;
	while(front != 0)
	{
		temp = front;
		front = front->next;
		delete temp;
	}
}

template <typename Item>
bool QueueTP<Item>::enqueue(const Item &item){
	if(isfull()){
		return false;
	}
	Node *add = new Node(item);
	items++;
	if (front == 0){
		front = add;
	}else{
		rear->next = add;
	}
	rear = add;
	return true;
}

//删除一个节点值的同时将这个节点值的值取出来
template <typename Item>
bool QueueTP<Item>::dequeue(Item &item){
	if(0 == front){
		return false;
	}
	item = front->item;
	items--;
	Node *temp = front;
	front = front->next;
	delete temp;
	if(0 == items){
		rear = 0;
	}
	return true;
}


int main() {
	using std::string;
	using std::cin;
	using std::cout;

	QueueTP<string> cs(5);
	string temp;

	while(!cs.isfull()){
		cout << "please enter your name. you will be served in the order of arrival.\n name: ";
		getline(cin, temp);
		cs.enqueue(temp);
	}

	cout << "The queue is full. Processing begins!\n";

	while(!cs.isempty()){
		cs.dequeue(temp);
		cout << "Now Processing " << temp << "....\n";
	}

	return 0;
}