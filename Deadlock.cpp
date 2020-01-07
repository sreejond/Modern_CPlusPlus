class LogFile
{
	std::mutex m_mutex;
	std::mutex m_mutex2;
	ofstream f;
public:
	LogFile()
	{
		f.open("log.txt");
	}// Need destructor to close file

	void shared_print(string msg, int id)
	{
		std::lock_guard<std::mutex> locker(m_mutex);
		std::lock_guard<std::mutex> locker2(m_mutex2);
		f << "From" << msg << ": " << id << endl;
	}

	void shared_print2(string msg, int id)
	{
		std::lock_guard<std::mutex> locker2(m_mutex2);
		std::lock_guard<std::mutex> locker(m_mutex);
		f << "From" << msg << ": " << id << endl;
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
		log.shared_print2(string("From main: "), i);

	t1.join();

	return 0;
}

// The above code is a classic deadlock example
// once solution could be lock all the mutex in the same order
class LogFile
{
	std::mutex m_mutex;
	std::mutex m_mutex2;
	ofstream f;
public:
	LogFile()
	{
		f.open("log.txt");
	}// Need destructor to close file

	void shared_print(string msg, int id)
	{
		std::lock_guard<std::mutex> locker(m_mutex);
		std::lock_guard<std::mutex> locker2(m_mutex2);
		f << "From" << msg << ": " << id << endl;
	}

	void shared_print2(string msg, int id)
	{
		std::lock_guard<std::mutex> locker(m_mutex);
		std::lock_guard<std::mutex> locker2(m_mutex2);
		f << "From" << msg << ": " << id << endl;
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
		log.shared_print2(string("From main: "), i);

	t1.join();

	return 0;
}


// use std::lock() 
// so that it can use it's deakdlock avoidance algorithm to lock those mutex
class LogFile
{
	std::mutex m_mutex;
	std::mutex m_mutex2;
	ofstream f;
public:
	LogFile()
	{
		f.open("log.txt");
	}// Need destructor to close file

	void shared_print(string msg, int id)
	{
		std::lock(m_mutex, m_mutex2);
		std::lock_guard<std::mutex> locker(m_mutex, std::adopt_lock);
		std::lock_guard<std::mutex> locker2(m_mutex2, std::adopt_lock);
		f << "From" << msg << ": " << id << endl;
	}

	void shared_print2(string msg, int id)
	{
		std::lock(m_mutex, m_mutex2);
		std::lock_guard<std::mutex> locker(m_mutex, std::adopt_lock);
		std::lock_guard<std::mutex> locker2(m_mutex2, std::adopt_lock);
		f << "From" << msg << ": " << id << endl;
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
		log.shared_print2(string("From main: "), i);

	t1.join();

	return 0;
}



class LogFile
{
	std::mutex m_mutex;
	std::mutex m_mutex2;
	ofstream f;
public:
	LogFile()
	{
		f.open("log.txt");
	}// Need destructor to close file

	void shared_print(string msg, int id)
	{
		std::lock_guard<std::mutex> locker(m_mutex);
		std::lock_guard<std::mutex> locker2(m_mutex2);
		f << "From" << msg << ": " << id << endl;
	}

	void shared_print2(string msg, int id)
	{
		{
			std::lock_guard<std::mutex> locker(m_mutex);
			usr_function();	// avoid calling user function
			//...
		}
		{
			std::lock_guard<std::mutex> locker2(m_mutex2);
			//...
		}
		f << "From" << msg << ": " << id << endl;
	}
};

/*
	Avoiding deadlock
	1. prefer locking single mutex
	2. avoid locking a mutex and then calling a user provided function 
	   (you dont know that function might lock your mutex or some different one)
	3. use std::lock() to lock more than one mutex
	4. lock the mutex in same order

	Locking Granularity:
	1. Fine-grained lock: protects small amount of data 
		(big chunk of you data in unprotected)
	2. Coarse-grained lock: protects big amount of data
		(you loose the potential of parallalism as most of the thread 
		need to wait long time for resource to be available)
*/
