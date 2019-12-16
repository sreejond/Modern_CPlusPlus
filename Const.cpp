/*
 * const
 * - A compile time constraint that an object can not be modified
*/

int main()
{
	const int i = 9;

	const int *p1 = &i;	// data is const, pointer is not
	p1++;

	int* const p2;	// pointer is const, data is not

	const int* const p3;	// data and pointer are both const

	int const *p4 = &i;
	const int *p4 = &i;

	// if const is on the left of *, data is const
	// if const is on the right of *, pointer is const

	// const away
	const int i = 9;
	const_cast<int&>(i) = 6;

	// make const
	int j;
	static_cast<const int&>(j) = 7;
}

/*
	Why use const
		1. Guards against inadvertent write to the variable. (at compile time)
		2. Self documenting
		3. Enables compiler to do more optimization, make code tighter
		4. const means the variable can be put in ROM (useful for embedded system)
*/


/////////// const overloading ///////////

// valid overloading
void foo() const;
void foo();

// valid overloading
void foo(int &i);
void foo(int const &i);

// invalid overloading
void foo(int i);
void foo(int const i);


//////////// logic constness vs bitwise constness /////////////

class BigArray {
	vector<int> v; // huge vector
	mutable int accessCounter;

	int* v2;	// another int array

public:
	int getItem(int index) const {
		accessCounter++;	// make it mutable for logic constness
		return v[index];
	}

	void setV2Item(int index, int x) const // it compiles as it is bitwise constness
	{										// it did not modified any member variable directly
		*(v2+index) = x;
	}
};

