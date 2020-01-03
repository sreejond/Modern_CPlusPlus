// Demystifying Operator new/delete

/* What happens when following code is executed? */

dog* pd = new dog();

/*
 * Step 1: operator new is called to allocate memory.
 * Step 2: dog's constructor is called to create dog.
 * Step 3: if step 2 throws an exception, call operator delete to free the memory allocated in step 1
*/

 delete pd;

 /*
  * Step 1: dog's destructor is called
  * Step 2: operator delete is called to free the memory
 */

  /*
   * Note: new handler is a function invoded when operator new failed to allocate memory
   * set_new_handler() installs a new handler and returns current handler
  */

   void* operator new(std::size_t size) throws(std::bad_alloc)
   {
   	while (true)
   	{
   		void* pMem = malloc(size);	// allocate memory
   		if (pMem)
   			return pMem;			// return the memory if successful

   		std::new_handler handler = std::set_new_handler(0);	// get new handler
   		std::set_new_handler(handler);

   		if (handler)
   			(*handler)();			// invoke new handler
   		else
   			throw bad_alloc();		// if new handler is null, throw exception
   	}
   }


   /*
    * Member operator new
   */

class dog
{
	...
public:
	static void* operator new(std::size_t size) throw(std::bad_alloc)
	{
		if (size == sizeof(dog))
			customNewForDog(size);
		else
			::operator new(size);
	}
	...
};

class yellowdog : public dog
{
	int age;
	static void* operator new(std::size_t size) throw(std::bad_alloc) {}	// need to override new operator
};

int main()
{
	yellowdog* py = new yellowdog();
}

/* SImililarly for operator delete */
class dog
{
	static void operator delete(void* pMemory)	throw()
	{
		customeDeleteForDog();
		free(pMemory);
	}

	virtual ~dog() {}	// we need to have virtual destructor for correct dog type to destory
};

class yellowdog : public dog
{
	static void operator delete(void* pMemory) throw()
	{
		customeDeleteForYellowDog();
		free(pMemory);
	}
};

int main()
{
	dog* pd = new yellowdog();
	delete pd;
}


/*
 * Why do we want to customize new/delete?
 *
 * 1. Usage error detection:
 *		- Memory lead detection/garbage collection
 *		- Array index overrun/underrun
 *
 * 2. Imporove efficiency:
 *		- Clustering related objects to reduce page fault
 *		- Fixed size allocation (good for applicatoin with many small objects)
 *		- Align similar size objects to same places to reduce fragmentation
 *
 * 3. Perform addictional tasks:
 *		- Fill the deallocated memory with 0's - security
 *		- collect usage statistics
*/

 /*
 	Writing a GOOD memory manager is HARD!

 	Before wiriting your own version of new/delete, consider:

 		- Tweak your compiler toward your needs
 		- Search for memeory management library, e.g. Pool library from Boost.
 */

/*
 * So the new handler must to do one of following things:
 * 1. Make more memory available
 * 2. Install a different new-handler
 * 3. Uninstall the new handler (passing a null pointer)
 * 4. Throw an exception bad_alloc or its descendent
 * 5. Terminate the program
*/

 int main()
 {
 	int *pGiant = new int[10000000000L];
 	delete[] pGiant;
 }

 Output:
 terminate called after throwing an instance of 'std::bad_alloc'


 void noMoreMem()
 {
 	std::cerr << "Unable to allocate memeory" << endl;
 	abort();
 }

 int main()
 {
 	std::set_new_handler(noMoreMem);
 	int *pGiant = new int[10000000000L];
 	delete[] pGiant;
 }

 Output:
 Unable to allocate memory


/* Class specific new-handler */

class dog
{
	int hair[10000000000L];
	std::new_handler origHandler;
public:
	static void noMoreMem()
	{
		std::cerr << "No more memory for doggy" << endl;
		std::set_new_handler(origHandler);	// restore old handler
		throw std::bad_alloc;
	}

	void* operator new(std::size_t size) throw(std::bad_alloc)
	{
		origHandler = std::set_new_handler(noMoreMem);
		void* pV = ::operator new(size);	// call global operator new
		std::set_new_handler(origHandler);	// restore old handler
		return pV;
	}
};