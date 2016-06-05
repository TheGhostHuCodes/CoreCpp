#include <type_traits>
#include <memory>
#include <string>
#include <ostream>
#include <iostream>

using namespace std;

void meow(const string&) { cout << "meow(const string&)" << endl; }

template <int N> void meow(const char (&)[N]) {
    cout << "meow(const char (&)[" << N << "])" << endl;
}

template <typename T> void helper(const T&, false_type) {
    cout << "Not a pointer!" << endl;
}
template <typename T> void helper(const T&, true_type) {
    cout << "I'm a pointer!" << endl;
}

// This guy is super grabby. It'll add const to all sorts of things.
template <typename T> void foo(const T& t) {
    //    helper(t, typename is_pointer<T>::type());
    helper(t, is_pointer<T>());
}

template <typename T> void foo(const T*) { cout << "foo(const T*)" << endl; }

struct Base {};
struct Derived : public Base {};
struct MoreDerived : public Derived {};

void boo(Base*) { cout << "All your Base are belong to us" << endl; }
void boo(Derived*) { cout << "whatever Derived" << endl; }

void boo(const shared_ptr<Base>&) {
    cout << "All your Base are belong to us" << endl;
}
void boo(const shared_ptr<Derived>&) { cout << "whatever Derived" << endl; }

int main() {
    meow("purr");
    string st("cat");
    meow(st);

    int* p = nullptr;
    // Specializes on the template "foo(const T&)"! This is because it's easier
    // to do this than to add const to the int*.
    foo(p);
    foo(1729);
    const int* q = nullptr;
    foo(q);

    MoreDerived* md = nullptr;
    boo(md);

    shared_ptr<Derived> spd;
    boo(spd);

    //    shared_ptr<MoreDerived> spmd;
    //    boo(spmd);

    return 0;
}
