#include <iostream>
#include <thread>
#include <mutex>
#include <string>
using namespace std;

std::mutex mu;

void shared_print(string msg, int id)
{
	std::lock_guard<std::mutex> guard(mu);
	//mu.lock();
	cout << msg << id << endl;
	//mu.unlock();
}

void function()
{
	for (int i = 0; i > -100; i--)
		shared_print(string("From t1: "), i);
}

int main()
{
	std::thread t1(function);

	for (int i = 0; i < 100; i++)
		shared_print(string("From main: "), i);

	t1.join();

	return 0;
}

// the above code will still fail as cout is global anyone can use it
// to make the resource protected do the followings

class LogFile
{
	std::mutex m_mutex;
	ofstream f;
public:
	LogFile()
	{
		f.open("log.txt");
	}// Need destructor to close file

	void shared_print(string msg, int id)
	{
		std::lock_guard<std::mutex> locker(m_mutex);
		f << "From" << msg << ": " << id << endl;
	}

	// Note: things to remember
	// Never return f to the outside world
	ofstream& getStream()	{return f;}
	// Never pass f as an argument to user provided function
	void processf(void fun(ofstream&))
	{
		fun(f);
	}
};

void function(LogFile& log)
{
	for (int i = 0; i > -100; i--)
		log.shared_print(string("From t1: "), i);
}

int main()
{
	LogFile log;
	std::thread t1(function, std::ref(log));

	for (int i = 0; i < 100; i++)
		log.shared_print(string("From main: "), i);

	t1.join();

	return 0;
}



class stack
{
	int* _data;
	std::mutex _mu;
public:
	void pop();	// pop off the item on top of the stack
	int& top();	// return the item on top
	//...
};

void function()
{
	int v = st.top();
	st.pop();
	process(v);
}

// is the above function() thread safe??
stack:
-
6
-
8
-
3
-
9
-

Thread A 					Thread B

int v = st.top(); //6
							int v = st.top();
st.pop();
							st.pop();
							process(v);
process(v);

// here we can see 6 is being processed twice, and 8 is lost
// because the interface is poorly designed

class stack
{
	int* _data;
	std::mutex _mu;
public:
	int& pop();	// pop off the item on top of the stack
	int& top();	// return the item on top
	//...
};

void function()
{
	int v = st.pop();
	process(v);
}

// this will solve the issue, now stack is thread safe
// but it's not exception safe, thats why STL do not return top
// element on pop(), as it is not exception safe

/*
	Avoiding Data Race:
	1. Use mutex to synchronize data access
	2. Never leak a handle of data to outside
	3. Design interface appropriately
*/