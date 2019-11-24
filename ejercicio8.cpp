#include <vector>
#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>

using std::vector; using std::endl; using std::cout; 

std::mutex mutex;
std::condition_variable cv;
int r = 0;
bool isReady(){return r!=0;}

void sort(vector<int> & bar);
void mergeSort(vector<int>&left,vector<int>& right,vector<int>& bars);
void printV(vector<int> &v);

int main() {
	vector<int> nums {2,4,1,25,27,35,23};
	
	std::thread t3([&nums](){
		sort(nums);
		r = 1;
		cv.notify_one();
	});
	std::thread t4(printV,std::ref(nums));
	t3.join();
	t4.join();

	
	return 0;
}

void sort(vector<int> & bar) {
	if (bar.size() <= 1) return;
	
	int mid = bar.size() / 2;
	vector<int> left;
	vector<int> right;

	for (size_t j = 0; j < mid;j++)
		left.push_back(bar[j]);
	for (size_t j = 0; j < (bar.size()) - mid; j++)
		right.push_back(bar[mid + j]);
	
	std::thread t1(sort,std::ref(left));
	std::thread t2(sort,std::ref(right));
	t1.join();
	t2.join();
		
	mergeSort(left, right, bar);
}

void mergeSort(vector<int>&left, vector<int>& right, vector<int>& bars)
{
	int nL = left.size();
	int nR = right.size();
	int i = 0, j = 0, k = 0;
	
	while (j < nL && k < nR) {
		if (left[j] < right[k]) {
			bars[i] = left[j];
			j++;
		}
		else {
			bars[i] = right[k];
			k++;
		}
		i++;
	}
	while (j < nL) {
		bars[i] = left[j];
		j++; i++;
	}
	while (k < nR) {
		bars[i] = right[k];
		k++; i++;
	}
}

void printV(vector<int>& v){
	std::unique_lock<std::mutex> lock(mutex);
	cv.wait(lock,isReady);
	for(auto it : v){
		cout << it << ' ';
	}
}
