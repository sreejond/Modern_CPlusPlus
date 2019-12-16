class Person {
public:
	Person(string name) : m_pName(new string(name)) {}
	// Person(const Person&) = delete; // copy constructor is deleted
	~Person() {}
	Person(Person&&) = default;
	void printName() { cout << *m_pName << endl; }

private:
	unique_ptr<string> m_pName;
};

int main()
{
	vector<Person> persons;
	// persons.push_back(Person("George"));
	// persons.emplace_back("George");	// construct the object in place (in the place allocated to the vector)
	// for emplace_back() to work the object need to be either copyable or movable
	Person p("George");
	persons.push_back(std::move(p));
	persons.back().printName();

	// can not work with p raw pointer any more as it have been moved
}