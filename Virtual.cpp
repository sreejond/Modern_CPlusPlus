/* Use virtual destructor in polymorphic base class. */

class Dog {
public:
	virtual ~Dog() { cout << "Dog destroyed" << endl; }
	virtual void bark() {}
};

class YellowDog : public Dog {
public:
	~YellowDog() { cout << "Yellow dog destroyed" << endl; }
};

class DogFactory {
public:
	static Dog* createYellowDog() { return (new YellowDog()); }
	//... create other dogs
};

int main()
{
	Dog* d = DogFactory::createYellowDog();
	//... do something with d

	delete d; // will only delete Dog() instead of YellowDog, 
			  // solution is to use virtual destructor in Dog() base class

	return 0;
}

// There is one more solution to do this without using virutal destructor


class Dog {
public:
	~Dog() { cout << "Dog destroyed" << endl; }
	virtual void bark() {}
};

class YellowDog : public Dog {
public:
	~YellowDog() { cout << "Yellow dog destroyed" << endl; }
};

class DogFactory {
public:
	static shared_ptr<Dog> createYellowDog() { return shared_ptr<YellowDog>(new YellowDog()); }
	//... create other dogs
};

int main()
{
	shared_ptr<Dog> d = DogFactory::createYellowDog();
	//... do something with d

	return 0;
}// here d will be destroyed and both Dog() and YellowDog() destructor will be called