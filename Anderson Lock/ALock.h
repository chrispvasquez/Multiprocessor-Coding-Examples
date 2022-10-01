// Chris Vasquez

using namespace std;

#include <iostream>
#include <thread>
#include <atomic>
#include <vector>


thread_local int mySlot;
//Thread Local variable for ALock class


/* Anderson Lock Class */

class ALock {

	private:

	   int size;
	   vector<bool> flags;
	   atomic<int> tail;


	public:

	   ALock(int);
	   ~ALock(){};
	   void lock();
	   void unlock();
};


ALock::ALock(int s){

	size = s;
	flags.resize(size);
	tail = 0;
	flags[0] = true;

}


void ALock::lock(){

	mySlot = tail.fetch_add(1);
	while(!flags[mySlot % size]){};
	flags[mySlot % size] = false;
}


void ALock::unlock(){

	flags[(mySlot + 1) % size] = true;
}
