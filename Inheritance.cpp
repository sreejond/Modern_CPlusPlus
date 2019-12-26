/*
	Public, Protected and Private Inheritance
*/

class B {

};

class D_priv : private B {};
class D_prot : protected B {};
class D_pub  : public B {};

/*
They specifies different access control from the derived class to the base class.

Access Control:
1. None of the derived classes can access anything that is private in B
2. D_pub inherits public members of B as public and the protected members of B as protected
3. D_priv inherits the public and protected members of B as private
4. D_prot inherits the public and protected members of B as protected

Casting:
1. Anyone can cast a D_pub* to B*. D_pub is a special kind of B
2. D_priv's members and friends can cast a D_priv* to B*
3. D_prot's members, firends and children can cast D_prot* to B*
*/

/* Detailed Example */

class B {
public:
	void f_pub()	{cout << "f_pub is called\n";}
protected:
	void f_prot()	{cout << "f_prot is called\n";}
private:
	void f_priv()	{cout << "f_priv is called\n";}
}

class D_pub : public B {
public:
	void f() 
	{
		f_pub();	// OK. D_pub's public function
		f_prot();	// OK. D_pub's protected function
		f_priv();	// ERROR. B's private function
	}
};

class D_prot : protected B {
public:
	using B::f_pub;	// to change the access control of the derived function
	void f() 
	{
		f_pub();	// OK. D_pub's protected function
		f_prot();	// OK. D_pub's protected function
		f_priv();	// ERROR. B's private function
	}
};

class D_priv : private B {
public:
	void f() 
	{
		f_pub();	// OK. D_pub's private function
		f_prot();	// OK. D_pub's private function
		f_priv();	// ERROR. B's private function
	}
};

int main ()
{
	D_pub D1;
	D1.f_pub();	// OK. f_pub() is D_pub's public function
	D_prot D2;
	D2.f_pub()	// Error. f_pub() is D_prot's protected function

	B* pB = &D1;	// OK
	pB = &D2;		// Error
}


/*
	Public inheritance: is-a relation. eg. D_pub is-a kind of a B
	Private inheritance: similar to has-a relation
*/

class ring {
public:
	void tinkle() {...}
};

/* Composition */
class Dog {
	ring m_ring;
public:
	void tinkle() { m_ring.tinkle(); }	// call forwarding
};

/* Private Inheritance */

class dog : private ring {
public:
	using ring:tinkle;
}

/*
 	Note: Composition is prefer over private inheritance
 	1. decoupled code. eg. ring and dog
 	2. if one need two ring member then composition is easier, private inheritance not possible
 	3. if one change the ring object in run-time composition is easier, private inheritance not possible
 */


/*
	Maintain is-a relationship:
	1. Precise definition of classes
	2. Don't override non-virtual functions
	3. Don't override default pramater values for virtual functions
	4. Force inheritance of shadowed functions
*/