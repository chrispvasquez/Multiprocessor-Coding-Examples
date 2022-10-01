// Chirs Vasquez
// HW2

#include <iostream>
#include <thread>
#include <string>
#include <mutex>
#include <condition_variable>
#include <vector>
#include <sstream>
#include <map>


class Bakery{
	private:
	   int n;
	   int counter;
	   vector<bool> flag;
	   vector<int> label;
	   map<thread::id, int> new_ids;
	   mutex mtx;

	public:

	   Bakery(int num);
	   // Contructor

	   ~Bakery();
	   // Destructor

	   void set_id(int num);
	   // Replaces arbitary thread IDs with integer

	   void increment_counter();
	   // Add 10000 to the counter

	   void print_counter();
	   // Print the current value of the counter

	   bool check_k(int i, vector<bool> flag, vector<int> label);
	   // Check part of the while condition

	   void lock();
	   // Lock function for Bakery

	   void unlock();
	   // Unlock function for Bakery

};
