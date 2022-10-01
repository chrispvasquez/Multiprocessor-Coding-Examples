// Chris Vasquez

using namespace std;

#include <iostream>
#include <thread>
#include <atomic>
#include <vector>
#include <sstream>
#include "ALock.h"

int main(){

	int sharedVar = 0;		// Counter shared between threads
	vector<thread> threads;
	ALock *myLock = new ALock(10);	// Anderson Lock for 10 Threads

	for(int i = 0; i < 10; i++){	//For 10 threads

	     threads.push_back(thread([&myLock, i, &sharedVar]() mutable {	// Lambda Function

	     for(int j = 0; j < 1000; j++){	// Increment counter 1000 times
		 stringstream ss;
                 myLock->lock();

				//Two below comments serve as tests to see which thread is incrementing at a time
				//ss << "Thread " << i << " is incrementing" << endl;
				//cout << ss.str();

	         sharedVar++;	//Increment counter
                 myLock->unlock();
	     }
	   }));
	}

	for(auto j = threads.begin(); j != threads.end(); ++j)	j->join();  //Join all the threads

	delete myLock; // Free up dynamic memory

	cout << "Shared Counter: " << sharedVar << endl;

	return 0;

}
