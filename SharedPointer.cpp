class Dog {
	string m_name;
public:
	Dog(string name) {cout << "Dog is created: " << name << endl; m_name = name;}
	Dog() {cout << "Nameless dog created" << endl; m_name = "nameless";}
	~Dog() {cout << "dog is destroyed: " << m_name << endl;}
	void bark() {cout << "Dog " << m_name << " rules!" << endl;}
};

void foo() 
{
	Dog* p = new Dog("Gunner");
	//...
	//delete p;
	//...
	p->bark(); // p is a dangling pointer- undefined behavior
}// memory leak

void foo() 
{
	shared_ptr<Dog> p(new Dog("Gunner")); // count = 1
	// 1. "Gunner" is created. 2. p is created
	// This code is not exception safe, because "Gunner" can be created but shared_ptr failed to create
	// because of lack of memory. And "Gunner" end up being unmanaged by shared_ptr

	{
		shared_ptr<Dog> p2 = p; // cout = 2
	}
	// count = 1
	p->bark();
}//count = 0

int main()
{
	// An object should be assigned to a smart pointer as soon as it is created. Raw pointer should not be used.
	Dog* d = new Dog("Tank");
	shared_ptr<Dog> p(d);	// p.use_count() == 1
	shared_ptr<DOg> p2(d);	// p2.use_count() == 1
}

// shortcut to create shared_ptr
int main()
{
	shared_ptr<Dog> p = make_shared<Dog>("Tank"); // faster and safer
	// make_shared() combine the above two setps into one step, so it's faster
	// and it's safer as it is exception safe

	(*p).bark();

	// Shared Pointer casting is possible as regular pointers
	// static_pointer_cast()
	// dynaminc_pointer_cast
	// const_pointer_cast()
}

void foo()
{
	shared_ptr<Dog> p1 = make_shared<Dog>("Gunner"); // using default deleter: operator delete
	shared_ptr<Dog> p2 = shared_ptr<Dog>(new Dog("Tank"),
		[](Dog* p) {cout << "Custom deleting."; delete p;});
	shared_ptr<Dog> p3(new Dog[3]); // dog[1] and dog[2] have memory leaks
	shared_ptr<Dog> p4(new Dog[3], [](Dog* p) {delete[] p;}); // All 3 dogs will be deleted when p4 goes out of scope
}

Dog* d = p1.get(); // returns the raw pointer

// delete d;

// shared_ptr<Dog> p2(d);

doghouse.saveDog(d); // dangling pointer

// Note: Never use the raw pointer once you have created shared_ptr. if really needed use it carefully