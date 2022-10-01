// Chris Vasquez
//HW1
//9/1/2020

using namespace std;

#include <unistd.h>
#include <iostream>
#include <vector>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <string>
#include <sstream>
#include "ReadWriteLock.h"


int main (){

	vector<thread> threads;
	SimpleReadWriteLock *L = new SimpleReadWriteLock();
	int x = 3; // Half the Number of writes/reads per thread
	int n = 10; //Number of threads

	for(int j = 0; j < n; j++){

	   threads.push_back(thread([&L, j, x]() {	//Reading Lambda Func
               int i = 0;

	       for (i = 0; i < x; i++){           //Tests the basic ability of reading
	         L->rLock(j);
		 L->rUnlock(j);
	       }

	       for (i = 0; i < x; i++)    L->rLock(j);    //Tests the ability of multiple consecutive reads by single thread
	       for (i = 0; i < x; i++)    L->rUnlock(j);

	   }));

	   threads.push_back(thread([&L, j, x]() mutable {   //Writing Lambda Func
	     int i = 0;

	     for (i = 0; i < x; i++){		//Tests the basic ability of writing
	       L->wLock(j);
	       L->wUnlock(j);
	     }

	     for (i = 0; i < x; i++)	L->wLock(j);	//Tests the ability of multiple consecutive writes by single thread
	     for (i = 0; i < x; i++)	L->wUnlock(j);
	   }));

	}

	for(auto j = threads.begin(); j != threads.end(); ++j){
	   j->join();
	}
	// wait for threads

	cout << "PROGRAM COMPLETE\n";

	return 0;
}
