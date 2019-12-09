#include <iostream>
#include <vector>

using namespace std;

int main()
{

    // 1. initializer_list
    vector<int> v1 = {1,2,3,4};
    vector<int> v2 {1,2,3,4};

    class MyVector {
    public:
        MyVector(const initializer_list<int>& v)
        {
            for (initializer_list<int>::iterator it = v.begin(); it != v.end(); it++)
            {
                m_vec.push_back(*it);
            }
        }

        vector<int> m_vec;

    };

    MyVector mv1 = {1,2,3,4};
    MyVector mv2{1,2,3,4};

    for (auto& v : mv1.m_vec)
        cout << v << " ";
    cout << endl;
    for (auto& v : mv2.m_vec)
        cout << v << " ";
    cout << endl;

    // 2. Uniform Initialization
    class MyClass   // aggregate class or struct
    {
    public:
        int m_a;
        string m_str;
    };

    MyClass cls{1, "dip"}; // Aggregate Initialization
    cout << cls.m_a << " " << cls.m_str << endl;

    class dog {
    public:
        dog(int age, string name)
        {

        }
    };

    dog d = {5, "tommy"};

    /* Uniform initialization search order
     * 1. initializer_list constructor
     * 2. regular constructor that takes the appropriate constructor
     * 3. Aggregate Initializer
    */

    // 3. auto type
    vector<int> v {1,2,3,4};
    for (vector<int>::iterator it = v.begin(); it != v.end(); it++)
    {
        cout << *it << " ";
    }
    cout << endl;
    for (auto it = v.begin(); it != v.end(); it++)
    {
        cout << *it << " ";
    }
    cout << endl;

    // 4. foreach
    for (int value : v)
        cout << value << " ";
    cout << endl;
    for (auto& value : v)
        cout << ++value << " ";
    cout << endl;

    // 5. nullptr
//    void foo(int i) {cout << "foo_int" << endl;}
//    void foo(char* pc) {cout << "foo _char*" << endl;}
//
//    foo(NULL); // Ambiguity
//    foo(nullptr); // call foo(char*)

    // 6. enum class
    enum apple {green, red};
    enum orange {big, small};
    apple a = green;
    orange o = big;
    if (a == o)
        cout << "green apple and big orange are the same\n";    // which is not true, as both of them are different type
    else cout << "green apple and big orange are not the same\n";

    enum class apple {green, red};
    enum class orange {big, small};
    apple a = apple::green;
    orange o = orange::big;
    if (a == o) // compile fails because we haven't define  operator== for apple and orange
        cout << "green apple and big orange are the same\n";
    else cout << "green apple and big orange are not the same\n";

    // so enum class is more type safe

    // 7. static_assert

    // run time assert
    assert(myPointer != NULL);

    // compile time assert (C++11)
    static_assert(sizeof(int) == 4);

    // 8. Delegating Constructor
    class cat {
    public:
        dog () {};
        dog (int a) {dog(); doOtherThings(a);} // in C++ 03 it will create to dog object
    };

    // C++ 03
    class cat{
        init() {}
    public:
        dog() {init();}
        dog(int a) {init(); dogOtherThings(a);}
    };

    /* Cons
     * 1. Cumbersome code. (extra function, duplicate init() call from different constructor)
     * 2. init() could be invoked by other functions
    */

    // C++11
    class cat {
    private:
        int age = 9; // allowed in class data member initialization. Every constructor initialize age with 9
    public:
        dog() {}
        dog(int a) : dog() {doOtherThings(a);}
    };
    // Limitation : dog() has to be called first

    // 9. override (for virtual function)

    // 10. final keyword
    class dog final { // no class can be derived from dog
    };

    class dog{
        virtual void bark() final; // no class can override bark()
    };

    // 11. Compiler generated default constructor
    class dog{
        dog(int age) {}
    };

    dog d; // Error: compiler will not generate the default constructor

    // C++11
    class dog {
        dog (int age);
        dog() = default; // force compiler to generate the default constructor
    };

    // 12. delete
    class dog{
        dog(int age) {}
    };

    dog a(2);
    dog b(3.0); // 3.0 is converted from double to int
    a = b; // compiler generated assignment operator

    // C++11
    class dog{
        dog(int age)    {}
        dog(double age) = delete;
        dog& operator=(const dog&) = delete;
    };
    // this is prevent the client to use the dog constructor with double parameter and copying dog object

    // 13. constexpr
    int arr[6];
    int A() {return 3;}
    int arr[A() + 3]; // compile error

    // C++11
    constexpr int A() {return 3;} // force the computation to happen at compile time
    int arr[A() + 3]; // create an array of size 6

    // write faster program with constexpr
    constexpr int cubed(int x) {return x*x*x;} // cubed need to be called by const parameter
    int y = cubed(1789); // compute at compile time

    // 14. New String Literals
    // C++03
    char* a = "string";

    // C++11
    char*       a = u8"string"; // to define an UTM-8 string
    char16_t*   b = u"string"; // to define an UTM-16 string
    char32_t*   c = U"string"; // to define an UTM-32 string
    char*       d = R"string \\"; // to define raw string

    // 15. lambda function
    cout << [] (int x, int y) {return x+y;} (3,4) << endl; // output 7
    auto f = [] (int x, int y) {return x + y;};
    cout << f(3,4) << endl; // output 7

    template<typename func>
    void filter(func f, vector<int> arr)
    {
        for (auto i : arr)
        {
            if (f(i))
            {
                cout << i << " ";
            }
        }
    }

    int main()
    {
        vector<int> v = {1,2,3,4,5,6};
        filter([](int x) {return x > 3;}, v);   // output 4 5 6
        filter([] (int x) {return x > 2 && x < 5;}, v); // output 3 4

        int y = 4;
        filter([&] (int x) {return x > y;}, v); // output 5 6
        // Note: [&] tells compiler that we want variable capture
    }

    return 0;
}
