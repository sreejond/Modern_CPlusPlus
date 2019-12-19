/* Resource Acquisition is Initialization (RAII) 
 *
 * Use objects to manage resources:
 * 		memory, hardware device, network handle, etc.
 */

Mutex_t mu = MUTEX_INITIALIZER;

void funcationA()
{
	Mutex_lock(&mu);
	... // do a bunch of things
	Mutex_unlock(&mu);	// will this line always be executed?
}

// Solution
class Lock {
private: 
	Mutex_t *m_pm;
public:
	explicit Lock(Mutex_t *pm) {Mutex_lock(pm); m_pm = pm;}
	~Lock()	{Mutex_unlock(m_pm);}
}

void functionaA()
{
	Lock mylock(&mu);
	... // do a bunch of things
	// the mutex will always be released when mylock is destroyed from stack
}

/* Conclusion:
 * 
 * The only code that can be guaranteed to be executed after exception is thrown
 * are the destructor of objects residing on the stack.
 *
 * Resource management therefore needs to be tied to the lifespan of suitable
 * objects in order to gain automatic deallocation and reclamation.
 */

/* Note 1:
 * Another good example of RAII : shared_ptr
 */

int functionA()
{
	std::shared_ptr<Dog> pd(new dog());
	...
}// the dog is destructed when pd goes out of scope (no more pointer points to pd)


// Note 2: 
// Another example:
class Dog;
class Trick;
void train(std::shared_ptr<Dog> pd, Trick dogtrick);
Trick getTrick();

int main ()
{
	train(shared_ptr<Dog> (new Dog()), getTrick());
}
// Question: What's the problem with the above code:

// What happens in train()'s parameter passing:
// 1. new Dog()
// 2. getTrick()
// 3. construct shard_ptr<Dog>
// The order of these operations are determined by compiler

// Conclusion: Don't combine storing objects in shared pointer with other statement

// Solution:

int main ()
{
	shared_ptr<Dog> pd(new Dog());
	train(pd, getTrick());
}

/* Note 3:
   What happens when resource management object is copied?
*/

Lock L1(&mu);
Lock L2(L1);

/* Solution 1:
 * Prohibit copying. delete copy constructor and copy assignement operator
 *
 * Solution 2:
 * Reference count the underlying resource by using shared_ptr
 */

template<class Other, class D> shared_ptr(Other *ptr, D deleter);
// The default value for D is "delete". e.g.:

class Lock {
private:
	std::shared_ptr<Mutex_t> pMutex;
public:
	explicit Lock(Mutex_t *pm) : pMutex(pm, Mutex_unlock) 
	{
		Mutex_lock(pm);
	}
};

Lock L1(&mu);
Lock L2(L1);