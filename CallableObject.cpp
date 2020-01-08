class A
{
public:
	void f(int x, char c)	{}
	long g(double x)	{return 0;}
	int operator()(int N) {return 0;}
};

// this are the various standard library function that work with callable objects
int main()
{
	A a;
	std::thread t1(a, 6);
	std:::async(std::launch::async, a, 6);
	std::bind(a, 6);
	std::cal_once(once_flag, a, 6);

	return 0;
}

void foo(int x)	{}

int main()
{
	A a;
	std::thread t1(a, 6);	// copy_of_a() in a different thread
	std::thread t2(std::ref(a), 6);	// a() in a different thread
	std::thread t3(std::move(a), 6);	// a in no longer usable in main thread
	std::thread t4(A(), 6);	// temp A, then moved to different thread
	std::thread t5([](int x){return x*x;}, 6);	// lambda
	std::thread t6(foo, 7);

	std::thread t7(&A::f, a, 8, 'w');	// copy_of_a.f(8, 'w') in a different thread
	std::thread t8(&A::f, &a, 8, 'w');	// a.f(8, 'w') in a different thread
}