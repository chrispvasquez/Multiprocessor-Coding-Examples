// Chris Vasquez
// HW2

using namespace std;

#include <iostream>
#include <thread>
#include <string>
#include <mutex>
#include <condition_variable>
#include <vector>
#include <sstream>
#include <map>
#include "bakery.h"

int main(){

	int n = 10;			// # of threads
	vector<thread> threads; 	// Vector to hold threads

	Bakery *test = new Bakery(n);	// Create Bakery object with "new" operator

	for(int i = 0; i < n; i++){

	   threads.push_back(thread([&test, i, n]() {

	   test->set_id(i);
	   test->lock();
	   test->increment_counter();
	   test->unlock();
	   test->print_counter();

	 }));

	}

	for(auto j = threads.begin(); j != threads.end(); ++j) j->join();

	cout << "PROGRAM COMPLETE\n";

	return 0;

}
