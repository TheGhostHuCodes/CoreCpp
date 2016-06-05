#include <string>
#include <ostream>
#include <iostream>

using namespace std;

// Primary template.
template <typename T> struct Kitty {
    static void Meow() { cout << "Kitty<T>::Meow()!" << endl; }
};

// Full or Explicit specializaiton.
template <> struct Kitty<const char*> {
    static void Meow() { cout << "Kitty<const char*>() yay!" << endl; }
};

// Partial specializaiton.
template <typename X> struct Kitty<X*> {
    static void Meow() { cout << "Kitty<X*>() yay!" << endl; }
};

template <typename T> void meow(T) { cout << "meow<T>()!" << endl; }

// Overloaded template, there is no such thing as a partially specialized
// function template. There are only partially specialized class templates.
template <typename X> void meow(X*) {
    cout << "meow(X*) is an overloaded template!" << endl;
}

template <> void meow(long) {
    cout << "meow(long) is an explicit/full specialization!" << endl;
}

// void meow(long) {
//    cout << "meow(long) is an ordinary function!" << endl;
//}

int main() {
    Kitty<int>::Meow();
    Kitty<const char*>::Meow();
    Kitty<double*>::Meow();

    meow(1729);
    meow(0L);
    meow(static_cast<double*>(nullptr));
    return 0;
}
