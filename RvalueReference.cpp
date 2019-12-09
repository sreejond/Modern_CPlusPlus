// C++11: Rvalue Reference
//
//	1. Moving Semantics
//	2. Perfect Forwarding
//
// What is lvalue and rvalue?
// 
// 1. Every C++ expression yield either a rvalue or a lvalue
// 2. If the expression has an identifiable memory address, it's lvalue; otherwise rvalue
 
/********* Move Semantics ***********/

// function overloading with lvalue reference parameter and rvalue reference parameter
// you can only overload the functions with lvalue reference and rvalue reference
void printInt(int& i)	{cout << "lvalue reference: " << i << endl;}
void printInt(int&& i)	{cout << "rvalue reference: " << i << endl;}
void printInt(int i) {} // will not work as it creates ambiguity with lvalue ref and rvalue ref funtions

 int main()
 {
 	int a = 5;	// a is a lvalue
 	int& b = a; // b is a lvalue reference (reference)
 	int&& c;	// c is a rvalue reference
 	
 	printInt(a);	// Call printInt(int& i)
 	printInt(6);	// Call printInt(int&& i)

 	return 0;
 }

 class boVector {
private:
	int m_size;
	double* m_arr;	// a big array

public:
	boVector(const boVector& rhs)	// copy constructor (doing deep copy)
	{
		m_size = rhs.m_size;
		m_arr = new double[m_size];
		for (int i = 0; i < m_size; i++)
		{
			m_arr[i] = rhs.m_arr[i];
		}
	}

	boVector(boVector&& rhs)	// move constructor (doing shallow copy)
	{
		m_size = rhs.m_size;
		m_arr = rhs.m_arr;
		rhs.m_arr = nullptr;
	}

	~boVector() {delete m_arr;}
 };

 void foo(boVector v);
 void foo_by_ref(boVector& v);

 boVector createBoVector();

 void main()
 {
 	boVector reusable = createBoVector();
 	foo(reusable); // call copy constructor
 	foo(createBoVector());	// if you dont have move constructor it will call copy constructor, 
 	//but this is rvalue which create a temp variable. so no need to call the expensive copy construtor 
 	// for the temp variable which will be destroyed momentarily. that's why move constructor is handy
 }

 int main()
 {
 	boVector reusable = createBoVector();
 	foo_by_ref(reusable);	// call no constructor (no expense)
 	foo(reusable);			// call copy constructor (expensive)
 	foo(std::move(reusable)); // call move constructor (almost no expense)
 	// after doing std::move() you should not use reusable anywhere in the code
 	//reusable is distroyed here
 }

 /*
  * Note 1: the most useful place for rvalue reference is overloading copy constructor and copy assignment operator,
  * to achive move semantics.
 */

 /*
  * Note 2: Move semantics is implemented for all STL containers, which means:
  * 	a. Move to C++11, your code will be faster wihout changing a thing.
  *		b. Passing-by-value can be used for STL containers
 */

  vector<int> foo () 
  {
  	return myvector;	// this is fine according to 2.b
  }

  void hoo(string s);	// this is also fine according to 2.b

  bool goo (vector<int>& arg)	// pass by reference if you use arg to carry data back from goo()

/*	Move constructor / Move assignment operator
 *  
 * Purpose: conveniently avoid costly and unnecessary deep copying
 *
 * 1. They are particularly powerful where passing by reference and passing by value are both used.
 *	  If you know that your object will always be passed by reference then you dont need move constructor
 *
 * 2. They give you finer control of which part of your object to be moved.
*/

/********* Perfect Forwarding ***********/

 void foo(boVector arg);
 // boVector has both move constructor and copy constructor

 template<typename T>
 void relay(T arg)
 {
 	foo(arg);
 }

int main () 
{
	boVector reusable = createBoVector();
	relay(reusable);
	relay(createBoVector());
}

/*
 * 1. No costly and unnecessary copy constructor of beVector is made.
 * 2. rvalue is forwarded as rvalue and lvalue is forwarded as lvalue
*/

 // Solution:
 template<typename T>
 void relay(T&& arg)
 {
 	foo(std::forward<T>(arg));
 }

 /*
  * Reference collapsing rules (C++11)
  * 1. T& & 	==> T&
  * 2. T& &&	==> T&
  *	3. T&& &	==> T&
  * 4. T&& &&	==> T&& 
 */

 template <class T>
 struct remove_reference;	// it removes reference on type T

 // T is int&
 remove_reference<int&>::type i; // int i;
 // T is int
 remove_reference<int>::type i; // int i; (no reference to remove)



 template<typename T>
 void relay (T&& arg)
 {

 }

 /*
  * rvalue reference is specified with type&&
  *
  * type&& is rvalue reference? : NO, T&& is rvalue reference if arg initialized with rvlaue
  *									  T&& is lvalue reference if arg initialized with lvalue
 */

  // T&& variable is initialized with rvlaue --> rvalue reference
  relay(9);	=> T = int&& => T&& = int&& && = int&&

  // T&& variable is initialized with lvalue => lvalue reference
  relay(x); => T = int& => T&& = int& && = int&&

// T&& is Universal Reference: rvalue, lvalue, const, non-const, etc ...
// Conditions:
// 1. T is a template type
// 2. Type deduction (reference collapsing) happens to T
//		- T is a function template type, not class template type

template <typename T>
void relay(T&& arg)
{
	foo(std::forward<T>(arg));
}

// Implementation of std::forward()
template<class T>
T&& forward(typename remove_reference<T>::type& arg)
{
	return static_cast<T&&>(arg);
}

// std::move() vs std::forward()
// both do static_cast()
std::move<T>(arg);		// Turn arg into rvalue type
std::forward<T>(arg);	// Turn arg to type of T&&
