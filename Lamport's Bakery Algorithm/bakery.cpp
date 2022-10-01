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
#include <algorithm>
#include "bakery.h"


Bakery::Bakery(int num){

	this->n = num;
	this->counter = 0;

	for (int i = 0; i < n; i++){
	   flag.push_back(false);
	   label.push_back(0);
	}
}


Bakery::~Bakery(){}


void Bakery::set_id(int num){

	unique_lock<mutex> lock (mtx);
	thread::id old_id = this_thread::get_id();
	new_ids.insert({old_id, num});
}


void Bakery::increment_counter(){
	for(int i = 0; i < 10000; i++) this->counter++;
}


void Bakery::print_counter(){
	stringstream stream;
	stream << this->counter << "\n";
	cout << stream.str();
}


bool Bakery::check_k(int i, vector<bool> flag, vector<int> label){
	for(int k = 0; k < n; k++)
	   if(k != i && flag[k] && (label[k] < label[i] || (label[k]==label[i] && k < i)))
	      return true;
	return false;
}


void Bakery::lock(){

	auto itr = new_ids.find(this_thread::get_id());
	int i = itr->second;

	flag[i] = true;
	label[i] = *max_element(label.begin(), label.end()) + 1;

	while(check_k(i, flag, label)){};
}


void Bakery::unlock(){

	auto itr = new_ids.find(this_thread::get_id());
	flag[itr->second] = false;
}
