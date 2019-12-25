// Type conversion:
//		1. Implicit type conversion
//		2. Explicit type conversion

/*
	1. static_cast
*/

int i = 9;
float f = static_cast<flot>(i);	// convert object from one type to another
dog d1 = static_cast<dog>(string("Bob"));	// Type conversion needs to be defined
dog* pd = static_cast<dog*>(new yellowdog());	// convert pointer/reference from one type to a related type (down/up cast)

/*
	2. dynamic_cast
*/

dog* pd = new yellowdog();	// implicit static_cast
yellowdog* py = dynamic_cast<yellowdog*>(pd);
// a. it convert pointer/reference from one type to a related type (down cast)
// b. run-time type check. if succeed, py==pd; if fail py == 0
// c. it requires the 2 types to be polymorphic (have virtual function)

/*
	3. const_cast
*/

const char* str = "Hello, world";	
char* modifiable = const_cast<char*>(str);	

// only works on pointer/reference
// only works on same type
// cast away constness of the object being pointer to

/*
	4. reinterpret_cast
*/

long p = 51110980;
dog* dd = reinterpret_cast<dog*>(p);	// re-interpret the bits of the object pointed to
// the ultimate cast that can cast one pointer to any other type of pointer.

/*
	C-style casting:
*/

short a = 2000;
int i = (int) a;	// c-like casdt notation
int j = int(a);		// funtional notation
// A mixture of static_cast, const_cast and reinterpret_cast

/*	
 * Generally C++ style of casts are preferred over the C-style, because:
 * 1. Easier to identify in the code.
 * 2. Less usage error. C++ style povides:
 *	a. Narrowly specified purpose of each cast and
 *	b. Run-time type check capability
*/
