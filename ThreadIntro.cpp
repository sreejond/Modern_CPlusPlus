/* Process vs Thread */

// IPS: Files, Message Queue

/*
	Multithreading:
		Pros:
			- Fast to start
			- Low overhead
			- Communicating through shared memeory is faster than interprocess communication chanel
		Cons:
			- Difficult to implement. Bunch of threading specifi issues that need to be carefully handled
			- Can't run on distributed system

	Mulitprocessing:
		Cons:
			- It is usally slow and complex to start a process
			  As OS need to devot a bunch of internal resources to mange the process
	  		- Process has a lot of overhead. As OS need to provide protection to ensure
	  		  one prcess doesn't step into another process
	  	Pros:
	  		- can run easily in distributed machiens

*/

#include <iostream>
#include <thread>
using namespace std;

void function1()
{
	std::cout << "Beauty is only skin-deep" << std::endl;
}

int main()
{
	std::thread t1(function1);	// t1 starts running
	//t1.join();	// main thread waits for t1 to finish
	t1.detach();	// t1 will run freely on its own -- daemon process

	...

	if (t1.joinable())
		t1.join();
}

// join() and detach() can be done only once

// if two or multiple thread shared common resources, 
// the thread own the resource need to be alive for other threads to access it