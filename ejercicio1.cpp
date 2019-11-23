#include <iostream>
#include <thread>
#include <mutex>
#include <vector>

using std::vector;

template<typename T>
class Race_condition{
public:
	std::mutex mutex;
	int sum1;
	void sum(vector<T> v){
		mutex.lock();
		sum1 = 0;
		for(auto it:v){
			sum1+=it;
		}
		std::cout << "La suma es: " << sum1 << std::endl;
		mutex.unlock();
	}

};

int main(){
	//Para utilizar el código para otro tipo de dato debe cambiarse el tipo de vector y el tipo de Race_condition
	vector<int>v {4,5,6};
	Race_condition<int> racer;
	std::thread t1([&]{
		racer.sum(v);
	});
	
	vector<int>v2{8,9,10};
	
	std::thread t2([&]{
		racer.sum(v2);
	});
	t1.join();
	t2.join();


return 0;
}
