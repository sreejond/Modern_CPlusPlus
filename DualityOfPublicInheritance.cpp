/*
	The Duality of Public Inheritance

	- Inheritance of Interface
	- Inheritance of Implementation
*/

class Dog
{
public:
	virtual void bark() = 0;
	void run() {cout << "I am running \n";}
	virtual void eat() {cout << "I am eating\n";}
protected:
	void sleep()	{cout << "I am sleeping";}
};

class YellowDog : public Dog
{
public:
	virtual void bark()
	{
		cout << "I am a yellow dog.\n";
	}
	void iSleep() {sleep();}
};

/*
	Types of Inheritance in C++:

	1. Pure virtual public function- inherit interface only.
	2. Non-virtual public function - inherit both interface and implementation
	3. Impure virtual public function - inherit interface and default impolementation
	4. Protected function - inherit implementation only

	As a software designer, it is very important to separate the concepts of interface and implementation
*/	

/*
	Interface Inheritance

	1. Subtyping
	2. Polymorphism
*/

virtual void bark() = 0;

/*
	Pitfalls:
	- be carefl of interface bloat
	- interfaces do not reveal implementation
*/

/*
	Implementation Inheritance
	- increase code complexity
	- not encouraged
*/

public:
	void run() {cout << "I am running \n";}
	virtual void eat() {cout << "I am eating\n";}
protected:
	void sleep()	{cout << "I am sleeping";}

/*
	Guidelines for implementation inheritance:
	1. do not use inheritance for code reuse, use composition
	2. minimize the implementation in base class. base classes should be thin.
	3. minimize the level of hierarchies in implementation inheritance.
*/

/* Note: If base class and derived calss shared some common implementation
	its better to create a helper class, and both base and derived class should
	have access to that helper class
*/