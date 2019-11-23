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
	std::cout <<"Waiting.." << std::endl;
	std::unique_lock<std::mutex> lock(mutex);
	cv.wait(lock,isReady);
	for(auto it : v){
		std::cout << it << " ";
	}
}

void primos(int a, int n, vector<int>& v1){
	int counter = 0;
	for(a;a<=n;a++){
        	for(int i=1;i<=a;i++){
			if(a%i==0)
				counter++;
		};
        	if(counter==2)
			v1.push_back(a);
        counter=0;
	};
	r = 1;
	cv.notify_one();
}


int main(){
	int a, n;
	a =1;
	std::cin >> n;
	vector<int> v1;
	thread t1(primos,a,n,std::ref(v1));
	thread t2(printV,std::ref(v1));
	t1.join();
	t2.join();

return 0;
}
