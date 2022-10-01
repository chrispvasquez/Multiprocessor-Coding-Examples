// Chris Vasquez
//HW2

using namespace std;

#include <iostream>
#include <thread>
#include <string>
#include <mutex>
#include <condition_variable>
#include <vector>
#include <sstream>
#include <map>
#include "filter.h"

int main(){

	int n = 10;					// # of Threads
	vector<thread> threads;				// Vector to hold threads

	Filter *test = new Filter(n);			// Create Filter object with "new" operator

	for(int i = 0; i < n; i++){

		threads.push_back(thread([&test, i, n]() {  //Lambda Function for Threads

		   test->set_id(i);			// Convert arbitrary IDs to integer IDs
		   test->lock();
		   test->increment_counter();		// Increment counter by 1000
		   test->unlock();
		   test->print_counter();		// Print the counter

		}));

	}

	for(auto j = threads.begin(); j != threads.end(); ++j) j->join();  // Join threads to main thread

	cout << "PROGRAM COMPLETE\n";

	return 0;
}
