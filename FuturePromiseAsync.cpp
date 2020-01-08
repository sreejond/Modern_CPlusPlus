#include <future>

using namespace std;

void factorial(int N)
{
	int res = 1;
	for (int i = N; i > 1; i--)
		res *= i;

	cout << "Result is: " << res << endl;
}

int main()
{
	std::thread t1(factorial, 4);

	t2.join();
	return 0;
}

// what if we dont want print the output in the console
// we want to get the output in the parent thread from child thread

std::mutex mu;
std::condition_variable cond;

void factorial(int N, int& x)
{
	int res = 1;
	for (int i = N; i > 1; i--)
		res *= i;

	cout << "Result is: " << res << endl;
	x = res;
}

int main()
{
	int x;
	std::thread t1(factorial, 4, std::ref(x));

	t2.join();
	return 0;
}

// for above solution we need to bring mutex and condition variable
// as we have shered variable x between these two threads
// which is unnecessarily complicated

int factorial(int N)
{
	int res = 1;
	for (int i = N; i > 1; i--)
		res *= i;

	cout << "Result is: " << res << endl;
	return res;
}

int main()
{
	std::future<int> fu = std::async(factorial, 4);
	int x = fu.get();	// wait for child thread to finish and return the result

	return 0;
}

// here, async() is a function and thread was a class
// you can only call fu.get() once
// async() will not always create a new child thread

int main()
{
	std::future<int> fu = std::async(std::deferred, factorial, 4);	// factorial() is not executed yet
	int x = fu.get();	// factorial() will execute in the same thread

	return 0;
}

// in that case async() will not execute the factorial() right a way
// when fu.get() is called it will execute the factorial() in the same thread

int main()
{
	std::future<int> fu = std::async(std::async, factorial, 4);	// create a new child thread to execute factorial()
	int x = fu.get();	

	return 0;
}

int main()
{
	std::future<int> fu = std::async(std::async | std::launch::deferred, factorial, 4);	// default parameter
	// based on the implementation thread will be created or not
	int x = fu.get();	

	return 0;
}

// how can we send data from parent to child?
// we need promise to send data from parent to child

int factorial(std::future<int>& f)
{
	int res = 1;

	int N = f.get();	// wait untill it get the value from the parent class
	for (int i = N; i > 1; i--)
		res *= i;

	cout << "Result is: " << res << endl;
	return res;
}

int main()
{
	std::promise<int> p;
	std::future<int> f = p.get_future();

	std::future<int> fu = std::async(std::launch::async, factorial, std::ref(f));

	// do something else
	std::this_thread::sleep_for(chrono::milliseconds(20));
	p.set_value(4);

	int x = fu.get();	

	return 0;
}

// if parent forget to set the value it promised there will be an exception

int factorial(std::future<int>& f)
{
	int res = 1;

	int N = f.get();	// exception: std::future_errc::broken_promise
	for (int i = N; i > 1; i--)
		res *= i;

	cout << "Result is: " << res << endl;
	return res;
}

int main()
{
	std::promise<int> p;
	std::future<int> f = p.get_future();

	std::future<int> fu = std::async(std::launch::async, factorial, std::ref(f));

	// do something else
	std::this_thread::sleep_for(chrono::milliseconds(20));
	p.set_exception(std::make_exception_ptr(std::runtime_error("To err is human")));
	// if you do no have any data available to set, you can set an exception by yourself
	//p.set_value(4);

	int x = fu.get();	

	return 0;
}

// Note: future and promise are not copiable, but they are movable

// if you have 10 threads, and you want to set same data as promised to everyone what you will do?
// one solution is you need 10 promise and future instance, as future.get() can be called only once
// you need to have 10 copy of these future variable
// That makes our code messy

int factorial(std::shared_future<int> sf)
{
	int res = 1;

	int N = sf.get();	
	for (int i = N; i > 1; i--)
		res *= i;

	cout << "Result is: " << res << endl;
	return res;
}

int main()
{
	std::promise<int> p;
	std::future<int> f = p.get_future();
	std::shared_future<int> sf = f.share();

	std::future<int> fu = std::async(std::launch::async, factorial, sf);
	std::future<int> fu2 = std::async(std::launch::async, factorial, sf);
	std::future<int> fu3 = std::async(std::launch::async, factorial, sf);
	//... 10 threads

	// do something else
	std::this_thread::sleep_for(chrono::milliseconds(20));
	p.set_value(4);

	int x = fu.get();	

	return 0;
}


// This is usefull for broadcast kind of communication model
// one thing to remember here, you can pass the shared future as copy