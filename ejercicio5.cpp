#include <iostream>
#include <thread>
#include <mutex>
#include <vector>
#include <condition_variable>
#include <algorithm>

using std::vector; using std::thread;
std::condition_variable cv;
std::mutex mutex;
int r = 0;
bool isReady(){return r!=0;}



void printV(vector<int>& v){
	std::unique_lock<std::mutex> lock(mutex);
	cv.wait(lock,isReady);
	for(auto it : v)
		std::cout << it << ' ';
	std::cout << std::endl;
}
 
void eliminar(int n, vector<int>& v){
	v.erase(std::remove(v.begin(), v.end(),n),v.end());
	r = 1;
	cv.notify_one();
}

int main(){
	int n;
	std::cin >> n;
	vector<int> v {3,4,5,3,3,4};
	thread t1(eliminar, n, std::ref(v));
	thread t2(printV,std::ref(v));
	t1.join();
	t2.join();
return 0;
}

