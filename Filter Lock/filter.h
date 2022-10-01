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

class Filter {

	private:

	   int n;
	   int counter;
	   vector<int> level;
	   vector<int> victim;
	   map<thread::id, int> new_ids;
	   mutex mtx;

	public:

	   Filter(int num);
	   // Constructor

	   ~Filter();
	    // Destructor

	   void set_id(int num);
	   // Replaces the arbitrary thread IDs with integer IDs

	   void increment_counter();
	   // Add 10000 to the counter

	   void print_counter();
	   //Print the current value of the counter

	   bool check_k(int me, int x, vector<int> level);
	   // Check part of the while condtion


	   void lock();
	   // Lock function for filter

	   void unlock();
	   // Unlock function for filter
};

