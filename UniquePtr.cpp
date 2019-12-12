// Unique Pointers: exclusive ownerships, light weight smart pointer

void test()
{
	unique_ptr<Dog> pD(new Dog("Gunner"));
	
	pD->bark();
	// pD does a bunch of different thing

	Dog* p = pD.release(); // five up the ownership of the object and return it

	pD.reset(new Dog("Smokey")); // destroy the owned object and hold a new object
	pD.reset();	// pD = nullptr; // destroy the owned object as it is not owned anymore

	if (!pD)
	{
		cout << "pD is empty" << endl;
	}
	else
	{
		cout << "pD is not empty" << endl;
	}
}

void test()
{
	unique_ptr<Dog> pD(new Dog("Gunner"));
	unique_ptr<Dog> pD2(new Dog("Smokey"));
	pD2->bark();
	pD2 = move(pD);	// this is how you transfer the ownership of one unique_ptr to another
	// 1. Smokey is destroyed
	// 2. pD2 becomes empty
	// 3. pD2 owns Gunner
	pD2->bark();
}

void f(unique_ptr<Dog> p)
{
	p->bark();
}

unique_ptr<Dog> getDog()
{
	unique_ptr<Dog> p(new Dog("Smokey"));
	return p; // since unique_ptr is pass by value, this pointer p will automatically use the move semantics
}

void test()
{
	unique_ptr<Dog> pD(new Dog("Gunner"));
	f(move(pD));
	if (!pD)
		cout << "pD is empty" << endl;
	unique_ptr<Dog> pD2 = getDog();
}

// for shared pointer we need to use the customer deleter to delete the array of pointers
// as unique_ptr is partially speciallized for array, we dont have to do it
void test()
{
	//shared_ptr<Dog> pDD(new Dog[3], [](Dog* p) {delete[] p;});
	unique_ptr<Dog[]> dogs(new Dog[3]);
}

// how to manage exception inside constructor
class Dog{
	//Bone* pB;
	unique_ptr<Bone> pB;	// This prevent memory leak even constructor fails.
	// if pB is not shared with others than unique_ptr is a better choice
public:
	string m_name;
	void bark()	{cout << "Dog: " << m_name << " rules!" << endl;}
	Dog() {pB = new Bone(); cout << "Nameless dog created" << endl; m_name = "Nameless";}
	Dog(string name) {cout << "Dog is created: " << name << endl; m_name = name;}
	~Dog() {delete pB; cout << "dog is destroyed: " m_name << endl;}
};