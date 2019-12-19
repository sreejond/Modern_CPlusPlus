/* Initialization Fiasco
 * 	- A subtle problem that can crash your program
 */

using namespace std;

Dog d("Gunner");

int main ()
{
	d.bark();

	return 0;
}

// in Dog.cpp file

Cat c("Smokey");

class Dog {
private:
	string _name;
public:
	Dog (char* name)
	{
		cout << "Constructing Dog " << name << endl;
		_name = name;
	}

	bark() 
	{
		cout << "Dog rules! My name is " << _name << endl;
		c.meow();
	}
};

class Cat {
private:
	string _name;
public:
	Cat (char* name)
	{
		cout << "Constructing Cat " << name << endl;
		_name = name;
	}

	meow() 
	{
		cout << "Cat rules! My name is " << _name << endl;
	}
};

// Either Dog() or Cat() constructor will be initialized first, so the program will crash

// Solution:

// in Singleton.h
class Dog;
class Cat;

class Singleton {
private:
	static Dog* pd;
	static Cat* pc;
public:
	~Singleton();
	static Dog* getDog();
	static Cat* getCat();
};

// In Singleton.cpp
Dog* Singleton::pd = nullptr;
Dog* Singleton::pc = nullptr;

Dog* Singleton::getDog()
{
	if (!pd)
		pd = new Dog("Gunner");
	return pd;
}

Cat* Singleton::getCat()
{
	if (!pc)
		pc = new Cat("Smokey");
	return pc;
}

Singleton::~Singleton()
{
	if (pd)	delete pd;
	if (pc)	delete pc;
	pd = nullptr;
	pc = nullptr;
}