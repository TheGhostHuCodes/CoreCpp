#include <iostream>
#include <ostream>
#include <vector>

namespace Foo {
namespace Bar {

template <typename T> struct Meow {
    void purr() { std::cout << "Foo::Bar::Meow<T>::purr();" << std::endl; }
};
}

// Use this to get the above template into the namespace Foo.
using Bar::Meow;
}

template <> struct Foo::Meow<int> {
    void purr() { std::cout << "Meow<int>::purr();" << std::endl; }
};

// Using-declarations
using std::vector;

namespace A {
struct X {};
struct Y {};
void f(int);
void g(X);
}

namespace B {

void f(int i) {
    f(i); // which f() is called? B::f() is called in infinite recursion. To get
          // access to A::f() a "using A::f" declaration could be used.
}

// void g(A::X x) {
//    g(x); // which g() is called? Ambiguous because of ADL, the parameter x of
//          // type A::X means that A::g() is in scope, but so is B::g().
//}

void h(A::Y y) {
    h(y); // which h() is called? Namespace A does not have a function h(), so
          // B::h() is called in infinite recursion.
}
}

int main() {
    std::cout << "Meow!" << std::endl;
    // Argument depended lookup is used here to find which operator<< to find.
    operator<<(std::cout, "Meow!\n");

    vector<int> v;

    using Foo::Meow;

    Meow<long> l;
    l.purr();

    Meow<int> i;
    i.purr();
}
