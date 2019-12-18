/*
 * Disallow Function
 *	1. Delete copy constructor and copy assignment operator if you dont want you object to be copyable.
 *	   Ex- OpenFile object whoulc not be copyable as we dont want same two object to write on the same file. It's ambiguous.
 *	2. Private Destructor: stay out of stack. It's particularly useful in embeded system, where stack is low and you can
 	   use your heap memory to create object there, instead of doing it in the stack.
*/