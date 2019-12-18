class Dog {
public:
	string m_name;
	Dog(string name) {m_name = name; cout << name << " is born." << endl;}
	~Dog() {cout << m_name << " is destroyed" << endl; throw 20;}
};

int main()
{
	try{
		Dog dog1("Henry");
		Dog dog2("Bob");
		dog1.bark();
		dog2.bark();
	}
	catch (int e)
	{
		cout << e << " is caught" << endl;
	}
} // this program will crash. as there are two exception pending. and C++ cant
  // have more than one exception pending

// Solution 1: Destructor swallow the exception

~Dog() {
	try {
		// Enclose all the exception prone code here
	} catch (MYEXCEPTION e) {
		// catch exception
	} catch (...) {

	}
}

// Solution 2: Move the exception-prone code to a different function.
class Dog {
public:
	string m_name;
	Dog(string name) {m_name = name; cout << name << " is born." << endl;}
	~Dog() {cout << m_name << " is destroyed" << endl;}
	void prepareToDestroy() {...; throw 20;}
};

int main()
{
	try{
		Dog dog1("Henry");
		Dog dog2("Bob");
		dog1.bark();
		dog2.bark();
		dog1. prepareToDestroy();
		dog2.prepareToDestroy();
	}
	catch (int e)
	{
		cout << e << " is caught" << endl;
	}
}


// Between this two solution we need to chose one of them based on the situation.
// where it is appropriate to do it from the Dog() will chose Sol1. Where it is 
// appropriate for Dog() client will chose Sol2.

// Note: do not call virtual function inside constructor and destructor