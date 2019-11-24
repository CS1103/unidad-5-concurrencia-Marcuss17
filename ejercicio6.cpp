#include <iostream>
#include <thread>
#include <mutex>

using std::cout;

struct node{
	int val;
	node* next;
};


class linkedList{
private:
	node nodo;
	node* head;
	node* tail;
	std::mutex mutex;
public:
	linkedList(){head = nullptr; tail = nullptr;}

	void push_back(int value){
		std::lock_guard<std::mutex> lock(mutex); 
		if(head == nullptr){
			node* newNode = new node();
			newNode -> val = value;
			newNode -> next = head;
			head = newNode;
			tail = newNode;
		}
		else{
			node* newNode = new node();
			newNode -> val = value;
			newNode -> next = head;
			head = newNode;	
		}
	}
	
	void pop_back(){
		node* temp = new node();
		temp = head;
		head = temp->next;
		delete temp;
	}
	
	void printList(){
		node* temp = new node();
		temp = head;
		while(temp != nullptr){
			cout << temp->val << ' ';
			temp = temp->next;
		}
	}

};


int main(){
	linkedList l1;
	std::thread t1(&linkedList::push_back, &l1,5);
	std::thread t2(&linkedList::push_back, &l1,10);
	std::thread t3(&linkedList::push_back, &l1,15);
	std::thread t4(&linkedList::push_back, &l1,20);
	t1.join();		
	t2.join();		
	t3.join();		
	t4.join();		
	l1.printList();



return 0;
}
