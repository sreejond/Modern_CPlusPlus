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
		//std::lock_guard<std::mutex> locker(m_mutex);
		std::unique_lock<mutex> locker(m_mutex, std::defer_lock);
		// do something else

		locker.lock();
		f << "From" << msg << ": " << id << endl;
		locker.unlock();
		//...

		locker.lock();
		//...
		locker.unlock();

		std::unique_lock<mutex> locker2 = std::move(locker);
	}	
};

/*
	lock_guard and unique_lock is not copyable
	lock_guard is not movable, but unique_lock is movable

	unique_lock provide more flixibility to achieve granurality, it it's not fee.
	if you want performance and dont need extra flexibility use lock_guard
*/


// in the above code we dont need to open the file. we can do the lazy initialization like below

class LogFile
{
	std::mutex m_mutex;
	ofstream f;
public:
	LogFile()
	{
	}

	void shared_print(string msg, int id)
	{
		if (!f.open())				// Lazy Initialization or Initialization Upon First Use Idiom
			f.open("log.txt");

		std::unique_lock<mutex> locker(m_mutex, std::defer_lock);
		f << "From" << msg << ": " << id << endl;
	}	
};

// Now we need to make it thread safe
class LogFile
{
	std::mutex m_mutex;
	std::mutex mu_open;
	ofstream f;
public:
	LogFile()
	{
	}

	void shared_print(string msg, int id)
	{
		if (!f.open())				// Lazy Initialization or Initialization Upon First Use Idiom
		{
			std::unique_lock<mutex> locker2(mu_open);
			f.open("log.txt");
		}

		std::unique_lock<mutex> locker(m_mutex, std::defer_lock);
		f << "From" << msg << ": " << id << endl;
	}	
};

// above solution is not thread safe, we need to do the followings
class LogFile
{
	std::mutex m_mutex;
	std::mutex mu_open;
	ofstream f;
public:
	LogFile()
	{
	}

	void shared_print(string msg, int id)
	{
		{
			std::unique_lock<mutex> locker2(mu_open);
			if (!f.open())				// Lazy Initialization or Initialization Upon First Use Idiom
			{
				f.open("log.txt");
			}
		}

		std::unique_lock<mutex> locker(m_mutex, std::defer_lock);
		f << "From" << msg << ": " << id << endl;
	}	
};

// This is thread safe now. But every time we need to lock and unlock the file open block.
// which hinder our performance in concurrency. Instead we can do it in a better way as below-

class LogFile
{
	std::mutex m_mutex;
	std::once_flag flag;
	ofstream f;
public:
	LogFile()
	{
	}

	void shared_print(string msg, int id)
	{
		std::call_once(flag, [&](){ f.open("log.txt"); });	// file will be opened only once by one thread

		std::unique_lock<mutex> locker(m_mutex, std::defer_lock);
		f << "From" << msg << ": " << id << endl;
	}	
};