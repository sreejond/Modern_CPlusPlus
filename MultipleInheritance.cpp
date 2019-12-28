/*
Multiple Inheritance
*/

		File
		/	\
InputFile	OutputFile
		\	/
		IOFile

class File 
{
public:
	string name;
	void open();
};

class InputFile : virtual public File
{
};

class OutputFile : virtual public File
{
};

class IOFile : public InputFile, public OutputFile	// one copy of open()
{
}; // Diamond Shape of hierarchy


// Fix initialization problem for base class
class File 
{
public:
	File (string name);
};

class InputFile : virtual public File
{
	InputFile(string name) : File(name)	{}
};

class OutputFile : virtual public File
{
	OutputFile(string name) : File(name) {}
};

class IOFile : public InputFile, public OutputFile	// one copy of open()
{
	IOFile(string name) : OutputFile(name), InputFile(name), File(name)	{}
}; 

// The rule is most derived class should initialize all base class constructor
// You need to do it when your base class have a custome constructor


/*
	Interface Segregation Principle

	Split large interface into smaller and more specific ones so that clients 
	only need to know about the methods that are of interest to them.
*/

class Engineer 
{
public:
	...; // 40 APIs
};

class Son
{
public:
	...; // 50 APIs
};

class Andy : public Engineer, Son {

};


/*
	Pure Abstract Class

	Abstract Class: A class has one or more pure virtual functions.

	Pure Abstract Classes:
	A class containing only pure virtual functions
		- no data
		- no concrete functions
*/

//Ex:
class OutputFile 
{
public:
	void write() = 0;
	void open() = 0;
};


/*
	Summary:

	1. Multiple inheritance is an important technique. e.g. ISP
	2. Derive only from PACs when using Multiple Inheritance.
*/