#include <type_traits>
#include <functional>
#include <algorithm>
#include <string>
#include <iostream>
#include <vector>

using namespace std;

template <typename T> void meow(T t) {
    cout << t << endl;
    t *= 2;
    cout << "Double t: " << t << endl;
}

template <typename T> void meow(T one, T two) {
    cout << one << " " << two << endl;
}

template <typename T> void meow2(T t) {
    typedef typename make_unsigned<T>::type U;
    U u = static_cast<U>(t);
    cout << u << endl;
}

template <typename T> void meow(T val, function<void(T)> f) { f(val); }

template <typename T> void meow(const basic_string<T>& s) {
    cout << "str " << s << endl;
}

template <typename T> void meow(const T* ptr) { cout << "ptr " << ptr << endl; }

int main() {
    vector<int> v{1, 7, 2, 9};
    // This won't compile because count_if is templated on two interators that
    // must be the same type. Here v.cbegin() is a const iterator while v.end()
    // is not const.
    // auto count =
    //         count_if(v.cbegin(), v.end(), [](int x) { return x % 2 == 1; });
    // cout << "Count odd in v: " << count << endl;

    // std::sort is templated on a RandomAccessIterator.
    sort(v.begin(), v.end());
    for (auto i : v) {
        cout << i << endl;
    }

    // Don't try and help the compiler like below.
    meow<int>(1729);
    // This here is template argument deduction.
    meow(1729);
    meow(17, 29);

    // This won't compile because there is no matching template.
    // meow(17, 29L);

    const int n = 1234;
    meow(n);

    int m = -1234;
    meow2(m);

    // The commented out code below fails because template argument deduction
    // can't figure out that the lambda type is of type function<void (T)>.
    // meow(1729, [](int x){ cout << "Hey I'm a lambda" << x << endl; });
    function<void(int)> fxn = [](int x) {
        cout << "Hey I'm a lambda: " << x << endl;
    };
    meow(1729, fxn);

    string s("peppermint");
    meow(s);
    meow("peppermint");

    return 0;
}
