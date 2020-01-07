std::deque<int> q;
std::mutex mu;

void function1()
{
	int count = 10;
	while (count > 0)
	{
		std::unique_lock<mutex> locker(mu);
		q.push_front(count);
		locker.unlock();
		std::this_thread::sleep_for(chrono::seconds(1));
		count--;
	}
}

void function2()
{
	int data = 0;
	while (data != 1)
	{
		std::unique_lock<mutex> locker(mu);
		if (!q.empty())
		{
			data = q.back();
			q.pop_back();
			locker.unlock();
			cout << "t2 got a vlaue from t1: " << data << endl;
		}
		else
		{
			locker.unlock();
		}
	}
}

int main()
{
	std::thread t1(function1);
	std::thread t2(function2);
	t1.join();
	t2.join();
	return 0;
}

// the thread2 is busy-waiting. we know busy-waiting is not good.

void function2()
{
	int data = 0;
	while (data != 1)
	{
		std::unique_lock<mutex> locker(mu);
		if (!q.empty())
		{
			data = q.back();
			q.pop_back();
			locker.unlock();
			cout << "t2 got a vlaue from t1: " << data << endl;
		}
		else
		{
			locker.unlock();
			std::this_thread::sleep_for(chrono::milliseconds(10));
		}
	}
}

// Now the problem is we dont know 10 milisecond is small or large time for thread2
// if it's a small time the thread will wake up and see that there in no data available
// if it's a large time than thread is not getting the data in right moment

std::deque<int> q;
std::mutex mu;
std::condition_variable cond;

void function1()
{
	int count = 10;
	while (count > 0)
	{
		std::unique_lock<mutex> locker(mu);
		q.push_front(count);
		locker.unlock();
		cond.notify_one();	// notify one waiting thread, if there is one
		//cond.notify_all();	// notify all the thread waiting
		std::this_thread::sleep_for(chrono::seconds(1));
		count--;
	}
}

void function2()
{
	int data = 0;
	while (data != 1)
	{
		std::unique_lock<mutex> locker(mu);
		cond.wait(locker, [](){ return !q.empty(); });	// spurious wake
		data = q.back();
		q.pop_back();
		locker.unlock();
		cout << "t2 got a vlaue from t1: " << data << endl;
	}
}

// cond.wait() takes mu, as thead2 is going into sleep it should not lock the mutex that others are waiting for
// so the condition variable is unlock the mutex and goto sleep and when it wake up it lock the mutex again and proceed

// after going into sleep with cond.wait(locker), thread2 can be wake up itselt also otherthan the notification from condition variable
// it's called spurious wake. to check that we use this lambda

// Condition Variables is good to synchronized the execution sequence of the thread, 
// i.e. threads are running in a fixed order