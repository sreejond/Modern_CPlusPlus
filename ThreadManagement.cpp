#include <iostream>
#include <thread>
using namespace std;

void function1()
{
	std::cout << "Beauty is only skin-deep" << std::endl;
}

/* A Functor is a object which acts like a function. Basically, a class which defines operator().

class MyFunctor
{
   public:
     int operator()(int x) { return x * 2;}
}

MyFunctor doubler;
int x = doubler(5);
*/

class Fctor 
{
public:
	void operator()()
	{
		for (int i = 0; i > -100; i--)
		{
			cout << "from t1: " << i << endl;
		}
	}
};

int main()
{
	Fctor fct;
	std::thread t1(fct);	// t1 starts running
	std::thread t1((Fctor()));	// t1 starts running

	// using RAII
	// Wrapper w(t1); in the destructor if Wrapper we can t1.join() instead of in the catch statement
	// so, when w goes out of scope it's destructor get called and join for t1
	
	try
	{
		for (int i = 0; i < 100; i++)
			cout << "from main: " << i << endl;
	}
	catch (...)	// catch the exception happen in main thread, so that we can join() the child thread
				// otherwise the program will terminate abruptly
	{
		t1.join();
		throw;	// rethrow the exception for other to catch
	}

	t1.join();
	return 0;
}

class Fctor 
{
public:
	void operator()(string msg)
	{
		cout << "t1 says: " << msg << endl;
	}
};

int main()
{
	string s = "Where there is no trust, there is no love";
	std::thread t1((Fctor()), s);	// argument pass by value to thread

	// using RAII
	// Wrapper w(t1); in the destructor if Wrapper we can t1.join() instead of in the catch statement
	// so, when w goes out of scope it's destructor get called and join for t1
	
	try
	{
		cout << "from main: " << msg << endl;
	}
	catch (...)	// catch the exception happen in main thread, so that we can join() the child thread
				// otherwise the program will terminate abruptly
	{
		t1.join();
		throw;	// rethrow the exception for other to catch
	}

	t1.join();
	return 0;
}

class Fctor 
{
public:
	void operator()(string& msg)
	{
		cout << "t1 says: " << msg << endl;
		msg = "Trust is the mother of deceit."
	}
};

int main()
{
	string s = "Where there is no trust, there is no love";
	std::thread t1((Fctor()), std::ref(s));	// argument pass by reference to thread, memory shared

	t1.join();

	cout << "from main: " << s << endl;

	return 0;
}

class Fctor 
{
public:
	void operator()(string& msg)
	{
		cout << "t1 says: " << msg << endl;
		msg = "Trust is the mother of deceit."
	}
};

int main()
{
	string s = "Where there is no trust, there is no love";
	cout << std::this_thread::get_id() << endl;

	std::thread t1((Fctor()), std::move(s));	// ownership is pass to the thread, 
												// argument is not valid in this thread anymore

	cout << t1.get_id() << endl;

	std::thread t2 = t1;	// error: thread is not copyable
	std::thread t2 = std::move(t1);	// it is movable

	t2.join();

	cout << "from main: " << s << endl;

	return 0;
}

int main()
{
	// Oversubscription: using more thread than our hardware can support 
	// (more than the number of core in the processor)

	std::thread::hardware_concurrency();	// Indication of how many thead we can use

	return 0;
}