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


SimpleReadWriteLock::SimpleReadWriteLock(){
	   writer = false;
	   readers = 0;
	   waitWriters = 0;
	}

SimpleReadWriteLock::~SimpleReadWriteLock(){};


void SimpleReadWriteLock::rLock(int num){

	   unique_lock<recursive_mutex> lock(mtx);

	   while (writer){
	    stringstream stream;
	    stream << "Reader " << num << " : Reader is Waiting...\n";
	    cout << stream.str();
	    condition.wait(lock);
	   }
	   readers++;

	   stringstream s;
	   s << "Reader " << num << " : Reading...\n";
	   cout << s.str();
}


void SimpleReadWriteLock::rUnlock(int num){
	   unique_lock<recursive_mutex> lock(mtx);
	   readers--;

	   stringstream s;
	   s << "Reader " << num << " : Done Reading!\n";
           cout << s.str();

	   if(readers == 0) condition.notify_all();
}


void SimpleReadWriteLock::wLock(int num){

	   stringstream s;
	   auto me = this_thread::get_id();
	   unique_lock<recursive_mutex> lock(mtx);

	   if(wOwner == me){
	     waitWriters++;
	     return;
	   }

	   while ((readers > 0 || writer) && waitWriters != 0) {
	      s << "Writer " << num << " : Writer is Waiting...\n";
	      cout << s.str();
	      s.str("");
	      condition.wait(lock);
	   }

	   writer = true;
	   wOwner = me;
	   waitWriters = 1;

	     s << "Writer " << num << " Writing...\n";
	     cout << s.str();
}


void SimpleReadWriteLock::wUnlock(int num){

	   stringstream s;
	   unique_lock<recursive_mutex> lock(mtx);

	   auto me = this_thread::get_id();

	   if(waitWriters == 0 || wOwner != me)	cout << "ILLEGAL MONITOR STATE EXCEPTION\n";


	   if(waitWriters > 1 && wOwner == me){
	     s << "Writer " << num  << " : Done Writing!\n";
	     cout << s.str();
	     s.str("");

	       s << "Writer " << num << " Writing...\n";
	       cout << s.str();
	       s.str("");
	   }

	   waitWriters--;

	   if(waitWriters == 0){
             s << "Writer " << num  << " : Done Writing!\n";
             cout << s.str();
             s.str("");
	     wOwner = nullId;

	     writer = false;
	     condition.notify_all();

	  }
}
