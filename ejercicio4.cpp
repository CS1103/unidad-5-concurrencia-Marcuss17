#include <iostream>
#include <thread>
#include <vector>
#include <mutex>
#include <condition_variable>

using std::vector; using std::thread;

std::condition_variable cv;
std::mutex mutex;
int r = 0;
bool isReady(){return r!=0;}


void printV(vector<int>& v){
	std::unique_lock<std::mutex> lock(mutex);
	cv.wait(lock,isReady);
	for(auto it : v){
		std::cout << it << " ";
	}
}

int fibo(int n){
	if(n == 0 || n == 1)
		return n;
	else{
		return fibo(n-2) + fibo(n-1);
	}
}

void showFibo(int num, vector<int>& v1){
	for(int i = 0; i < num; i++){
		v1.push_back(fibo(i));
	}
	r =1;
	cv.notify_one();	
}

int main(){
	int num;
	std::cin >> num;
	vector<int> v1;
	thread t1(showFibo,num,std::ref(v1));
	thread t2(printV,std::ref(v1));
	t1.join();
	t2.join();

return 0;
}

