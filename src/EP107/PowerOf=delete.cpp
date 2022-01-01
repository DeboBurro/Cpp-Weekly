#include <utility>

// Ref : 
//  c++ weekly : https://www.youtube.com/watch?v=aAvjUU0m6AU
//  Professor Hank Stalica : https://www.youtube.com/watch?v=xIEQL9MI2s4 

// in C++ 11, we can use `delete` to delete a function to prevent a function from being called
// Usages : 
// 1. Delete methods automatically created by compiler: copy construct, default constructor, etc
// 2. Avoid data loss
// 3. Prevent using the heap (delete new operator)
// 4. Prevent templates from being used in different ways

// syntax looks like 
// void foo() = delete;

template <typename T >
class Boo
{
    private:
    T x;

    public:
    Boo(T y):x(0) {}

    // In this way, people can prevent constructor with double be used 
    Boo(double) = delete;
};

class Foo
{
    private:
    int x;

    public:
    // default constructor
    Foo() : x(0) {};
    // make sure a copy constructor can never get created 
    Foo(const Foo&) = delete;
    // make sure the assignment cannot be called
    Foo& operator=(const Foo&) = delete;

    // Make sure no data loss, by not allowing instantiate using double
    Foo(int y) { x = y;}
    Foo(double) = delete;

    // Prevent using heap by not allowing using `new`
    void* operator new(std::size_t) = delete;

};

struct S
{
    S() = default;
    S(S &&) = default;
    // S(const S &&) = default;
    S(const S &&) = delete;
    S &operator=(const S &) = default;
    S &operator=(S&&) = default;
    S &operator=(const S &&) = delete;

    template<typename T>
    constexpr void do_something(T) const noexcept {};
    
    void do_something(double) const noexcept = delete;

};

int main(){
    // Example 1: https://www.youtube.com/watch?v=aAvjUU0m6AU
    S s;
    S s2;
    s2 = std::move(s);
    // pass by 1.0 will have no warning
    s2.do_something(1.0f);

    // Example 2: https://www.youtube.com/watch?v=xIEQL9MI2s4
    Foo f;
    Foo m(2.5);
    // The error below shows Foo(const Foo&) cannot be referenced because it's deleted
    Foo g(f);
    // assignment operator is also deleted
    f = m;

    // prevent using heap
    auto f = new Foo;

    Boo<int> b(99);
    Boo<double> k(1.234);

    return 0;
}