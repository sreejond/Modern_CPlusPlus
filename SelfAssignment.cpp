/* Implementing Assignement Operator */

/* Solution 1 */
class collar;
class Dog {
	collar* pCollar;
	Dog& operator=(const dog& rhs)
	{
		if (this == &rhs)	return *this;

		collar* pOrigCollar = pCollar; // save this in a temp variable, 
									   // for excidental exception in collar() construtor
		pCollar = new collar(*rhs.pCollar);
		delete pOrigCollar;

		return *this;
	}
};


/* Solution 2 : Delegation */
class collar;
class Dog {
	collar* pCollar;
	Dog& operator=(const dog& rhs)
	{
		*this->pCollar = *rhs.pCollar; // member by member copyting of collars or
									   // call collar's operator=
		return *this;
	}
};

// Solution 2 is preferable then Solution 1