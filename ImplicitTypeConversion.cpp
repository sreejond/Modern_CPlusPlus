class Dog {
public:
	Dog(string name) {m_name = name;}	// no explicit
	// if you only want to define a constructor, and no implicit type
	// coversion, always put "explicit" before the constructor to avoid
	// inadvertent type conversion.

	// string getName() {return m_name;}
	operator string () const {return m_name;}

private:
	string m_name;
};

void main()
{
	string dogname = "Bob";
	dog dog1 = dogname; // implicit conversion
	string dog2 = dog1;	// a type as I have a string operator() as member
	printf("My name is %s.\n", dog1);
}

/* PRINCIPLE: make interface easy to use correctly and hard to use incorrectly.
   How hard is enough? Ideally, uncompilable.

   General guideline:
   		1. Avoid defining seemingly unexpected conversion.
   		2. Avoid defining two-way implicit conversion.
*/

class Rational {
public:
	Rational(int numberator = 0, int denominator = 1):
		num(numberator), den(denominator)	{}

	int num;
	int den;

	const Rational operator* (const Rational& rhs)
	{
		return Rational(num * rhs.num, den*rhs.den);
	}

	operator int ()	{return num/den;}
};

int main()
{
	Rational r1 = 23;
	Rational r2 = r1 * 2; // compiler will complain, as it will be consufes
						  // to see operator* and operator int()
	Rational r3 = 3 * r1;
}

// Solution:
// 		Move the multiplication outside of the class
const Rational operator* (const Rational& lhs, const Rational& rhs)
{
	return Rational(lhs.num*rhs.num, lhs.den*rhs.den);
}