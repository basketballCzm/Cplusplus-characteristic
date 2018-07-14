#include <iostream>
#include <vector>
#include <numeric>
using namespace std;

template <class T>
T add_all_type(T a, T b){
	return a+b;
}

// init value no change
template <class InputIterator, class T>
T noop_accumulate(InputIterator first, InputIterator last, T init){
	while (first != last){
		init = init + *first;
		++first;
	}
	return init;
}

template <class InputIterator, class T, class BinaryOperation>
T op_accumulate(InputIterator first, InputIterator last, T init, BinaryOperation binary_op){
	while (first != last){
		init  = binary_op(init, *first);
		++first;
	}
	return init;
}


int main(){
	int ival;
	vector<int> ivec;
	cout << "enter some integers(ctrl+z to end): " << endl;
	// EOF is the end
	while(cin >> ival){
		ivec.push_back(ival);
	}
	/*
	cout << "summation of elements in the vector: "
		 << accumulate(ivec.begin(), ivec.end(), 0)
		 << endl;
	*/
	/*
	cout << "summation of elements in the vector: "
		 << noop_accumulate(ivec.begin(), ivec.end(), 0)
		 << endl;
	*/
	// This be able to <float> 
	cout << "summation of elements in the vector: "
		 << op_accumulate(ivec.begin(), ivec.end(), 0, plus<int>())
		 << endl;

	cout << add_all_type<double>(2,5) << endl;
	return 0;
}