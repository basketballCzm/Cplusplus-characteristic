#include <iostream>
#include <algorithm>

//sort 从小到大进行排序 sort(start, end, 排序方法)

bool complare(int a, int b){
	return a > b;
}

int main(){
	int a[6] = {45,34,78,98,2,44};
	char b[6] = "fdgcd";

	std::sort(a,a+6);
	for (int i = 0; i < 6; i++){
		std::cout << a[i] << " ";
	}
	std::cout << std::endl;

	std::sort(a,a+6,complare);

	for (int i = 0; i < 6; i++){
		std::cout << a[i] << " ";
	}
	std::cout << std::endl;

	std::sort(a, a+6, std::less<int>());
	for (int i = 0; i < 6; i++){
		std::cout << a[i] << " ";
	}
	std::cout << std::endl;

	std::sort(a, a+6, std::greater<int>());
	for (int i = 0; i < 6; i++){
		std::cout << a[i] << " ";
	}
	std::cout << std::endl;

	std::sort(b, b+5, std::less<char>());
	for (int i = 0; i < 5; i++){
		std::cout << b[i] << " ";
	}
	std::cout << std::endl;
	return 0;
}