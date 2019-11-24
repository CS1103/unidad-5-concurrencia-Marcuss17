#include <iostream> 
#include <thread>
#include <mutex>
#include <vector>
#include <algorithm>

std::mutex mutex;
 
int binarySearch(int arr[], int l, int r, int x) 
{ 
    if (r >= l) { 
        int mid = l + (r - l) / 2; 
        if (arr[mid] == x) 
            return mid; 
  
        if (arr[mid] > x) 
            return binarySearch(arr, l, mid - 1, x); 
  
        return binarySearch(arr, mid + 1, r, x); 
    } 
    return -1; 
} 
 
int main(void) 
{	
	int arr[] = { 2, 3, 4, 10, 40 }; 
	int n = sizeof(arr) / sizeof(arr[0]);
	std::vector<std::thread> workers;
	for(int i = 0; i < std::thread::hardware_concurrency();	i++){
		workers.push_back(std::thread([&](){
		mutex.lock();
		int result = binarySearch(arr,0,n-1,i);
     		(result == -1) ? std::cout << "Element is not present in array\n"
		: std::cout << "Element is present at index\n" << result; 
		mutex.unlock();
		}));
	}
	std::for_each(workers.begin(),workers.end(),[](std::thread & th){
		th.join();
	});
    return 0; 
} 
