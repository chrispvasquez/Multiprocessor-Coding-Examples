//Chris Vasquez
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


Filter::Filter(int num){

      this->n = num;
      this->counter = 0;
      victim.resize(n);

      for(int i = 0; i < n; i++){	// n = 10
	   level.push_back(0);
      }
}


Filter::~Filter(){}


void Filter::set_id(int num){

       unique_lock<mutex> lock (mtx);
       thread::id old_id = this_thread::get_id();
       new_ids.insert({old_id, num});
}


void Filter::increment_counter(){
       for(int i = 0; i < 10000; i++) this->counter++;
}


void Filter::print_counter(){
	stringstream stream;
	stream << this->counter << "\n";
	cout << stream.str();
}


bool Filter::check_k(int me, int x, vector<int> level){
          for (int k = 0; k < n; k++)
               if(k != me && level[k] >= x)
	         return true;
          return false;
}


void Filter::lock(){

	  auto itr = new_ids.find(this_thread::get_id());
	  int me = itr->second;
          for(int i = 1; i < n; i++){
             level[me] = i;
	     victim[i] = me;

             while(this->check_k(me, i, level) && victim[i] == me){};
          }
}


void Filter::unlock(){
	 auto itr = new_ids.find(this_thread::get_id());
         int me = itr->second;
         level[me] = 0;
}
