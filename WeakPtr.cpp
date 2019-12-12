// weak pointer has no ownership of the pointed object

class Dog
{
	// shared_ptr<Dog> m_pFriend;	// cyclic reference
	weak_ptr<Dog> m_pFriend;	// Dog* m_pFriend
public:
	string m_name;
	void bark() {cout << "Dog " << m_name << " rules!" << endl;}
	Dog(string name) {cout << "Dog is created: " << name << endl; m_name = name;}
	~Dog() {cout << "dog is destroyed: " << m_name << endl;}
	void makeFriend(shared_ptr<Dog> f) {m_pFriend = f;}
	void showFriend() 
	{
		if (!m_pFriend.expired())	cout << "My friend is: " << m_pFriend.lock()->m_name << endl;
	}
};

int main()
{
	shared_ptr<Dog> pD(new Dog("Gunner"));
	shared_ptr<Dog> pD2(new Dog("Smokey"));
	pD->makeFriend(pD2);
	pD2->makeFriend(pD);
	pD->showFriend();
}

// Weak pointer is just like a raw pointer, but it provide aditional safety with the expired() method 
// to check if the pointed object is still valid