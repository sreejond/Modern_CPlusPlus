class Dog {
public:
	virtual Dog* clone() {return new Dog(*this);}	// co-variant return type
};

class Yellowdog {
public:
	virtual Yellowdog* clone() {return new Yellowdog(*this);}
};

void foo(Dog* d)	// d is a Yellowdog
{
	// Dog* c = new Dog(*d);	// c is a dog
	Dog* c = d->clone();	// now c is a Yellowdog

	//....
}

int main()
{
	Yellowdog d;
	foo(&d);
}