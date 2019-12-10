/*
 * C++03:
 * 1. default constructor (generated only if no constructor defined by user)
 * 2. copy constructor (generated if no 5, 6 declared by user)
 * 3. copy assignment operator (generated if no 5, 6 declared by user)
 * 4. destructor
 *
 * C++11:
 * 5. move constructor (generated only if 2,3,4,6 not declared by user)
 * 6. move assignment operator  (generated only if 2,3,4,5 not declared by user)
*/

class dog {
	//C++03
	Dog();							//default constructor
	Dog(const Dog&);				//copy constructor
	Dog& operator= (const Dog&);	// copy assignment operator
	~Dog();							// default destructor

	//C++11
	Dog(Dog&&);						// move constructor
	Dog& operator= (Dog&&);			// move assignement operator
};


// Note: From C++11 rules to create compiler generated functions are deprecated
/*
 * C++03:
 * 1. default constructor (generated only if no constructor defined by user)
 * 2. copy constructor (generated if no 3,4 5, 6 declared by user)
 * 3. copy assignment operator (generated if no 2,4 5, 6 declared by user)
 * 4. destructor
 *
 * C++11:
 * 5. move constructor (generated only if 2,3,4,6 not declared by user)
 * 6. move assignment operator  (generated only if 2,3,4,5 not declared by user)
*/

class dog {
	//C++03
	Dog();							//default constructor
	Dog(const Dog&);				//copy constructor
	Dog& operator= (const Dog&);	// copy assignment operator
	~Dog();							// default destructor

	//C++11
	Dog(Dog&&);						// move constructor
	Dog& operator= (Dog&&);			// move assignement operator
};

// Basically C++11 prevent the abuse of compiler generated funtions in C++03 by imposing the new rules
// which implies explicite declaration of necessary functions