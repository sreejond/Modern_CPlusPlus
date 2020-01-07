/*
	Code reuse: Inheritance vs Composition
*/

class BaseDog 
{
	... // common activities	
};

class BullDog : public BaseDog
{
	... // call the common activities to perfome more tasks	
};

class ShepherdDog : public BaseDog
{
	... // call the common activities to perfome more tasks.	
};

// Class name should not be BaseDog something like this.
// Later its not easilly extensible, e.g. if you need one more base class
// what would you name it, BaseBaseX. NO

// Correct way of code reuse with inheritance
class Dog 
{
	... // common activities	
};

class BullDog : public Dog
{
	... // call the common activities to perfome more tasks	
};

class ShepherdDog : public Dog
{
	... // call the common activities to perfome more tasks.	
};



// Code reuse with composition
class ActivityManager
{
	...// common activities
};

class Dog
{
	...
};

class BullDog : public Dog
{
	ActivityManager* pActMngr;
	... // call the common activities through pActMngr
};

class ShepherdDog : public Dog
{
	ActivityManager* pActMngr;
	... // call the common activities through pActMngr
};


/*
	Code reuse : composition is better than inheritance

	1. Less code coupling between reused code and reuser of the code
		a. child class automatically inherits all parent class's public members
		b. child class can access parent's protected members.
			- Inheritance breaks encapsulation

	2. Dynamic binding
		a. Inheritance is bound at compile time
		b. composition can be bound either at compile time or at run time
*/

class OutdoorActivityManager : public ActivityManager {...}

class IndoorActivityManager : public ActivityManager {...}


/*
	3. Flexible code construct
	Dog 			AcivityManager

	BullDog 		OutdoorActivityManager
	ShepherdDog 	IndoorActivityManager
	...				...
*/