#include <iostream>
#include <thread>
#include <vector>

using std::thread; using std::vector;


template<typename cnt>
void printCnt(cnt c){
	for(auto it : c){
		std::cout << it << " "; 
	}
}

template<typename container>
void incremento(container& c,int n){
	for(auto& it : c){
		it += n;
	}
	printCnt(c);
}

int main(){
	vector<int> v1{4,5,6};
	int n = 4;
	thread t1(incremento<vector<int>>, std::ref(v1), n);
	t1.join();

}
