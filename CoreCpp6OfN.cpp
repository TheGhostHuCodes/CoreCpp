#include <type_traits>
#include <memory>
#include <algorithm>
#include <functional>
#include <vector>
#include <ostream>
#include <iostream>

using namespace std;

struct SmartPtr {
    explicit operator bool() const { return true; }
};

void func(bool) {}

template <typename C, typename F = less<typename C::value_type>>
void Sort(C& c, F f = F()) {
    sort(c.begin(), c.end(), f);
};

template <typename C> void Print(const C& c) {
    for (auto& e : c) {
        cout << e << " ";
    }
    cout << endl;
}

class Meow {
  public:
    Meow() : Meow(1729, 1234, 3.14, "meow") { cout << "Meow()" << endl; }
    explicit Meow(int n) : Meow(n, n, 3.14, "meow") {
        cout << "Meow(int n)" << endl;
    }
    Meow(int n, int x, double d, const string& s) : _n(n), _x(x), _d(d), _s(s) {
        cout << "Meow(int n, int x, double d, const string& s)" << endl;
    }

  private:
    int _n;
    int _x;
    double _d;
    string _s;
};

template <typename T, typename... Args>
unique_ptr<T> make_unique_helper(false_type, Args&&... args) {
    return unique_ptr<T>(new T(forward<Args>(args)...));
}

template <typename T, typename... Args>
unique_ptr<T> make_unique_helper(true_type, Args&&... args) {
    static_assert(
        extent<T>::value == 0,
        "make_unique<T[N] is forbidden, please use make_unique<T[]>().");
    typedef typename remove_extent<T>::type U;
    return unique_ptr<T>(new U[sizeof...(Args)]{forward<Args>(args)...});
}

template <typename T, typename... Args>
unique_ptr<T> make_unique(Args&&... args) {
    return make_unique_helper<T>(is_array<T>(), forward<Args>(args)...);
}

int main() {
    cout << R"(meow\n\t
foo Hello "world..." )"
         << endl;

    SmartPtr p;

    // If the bool conversion function was not explicit then the following lines
    // of code would compile.
    // cout << p * 1729 << endl;
    // func(p);

    if (p) {
        cout << "true!" << endl;
    } else {
        cout << "false!" << endl;
    }

    vector<int> v{11, 13, 5,  73, 47, 31, 89, 2,  97, 41, 61, 19, 29,
                  59, 67, 89, 53, 2,  37, 43, 17, 47, 89, 79, 23, 61,
                  83, 7,  83, 11, 3,  11, 59, 71, 37, 29, 19};

    Print(v);
    Sort(v);
    Print(v);
    Sort(v, greater<int>());
    Print(v);

    cout << "--" << endl;
    Meow m1;
    cout << "--" << endl;
    Meow m2(9);
    cout << "--" << endl;
    Meow m3(0, 0, 0.0, "");
    cout << "--" << endl;

    int x{1729};
    cout << x << endl;

    auto a = make_unique<int>(1729);
    cout << *a << endl;

    auto s = make_unique<string>(5, 'x');
    cout << *s << endl;

    auto b = make_unique<int[]>(11, 22, 33);
    cout << b[0] << " " << b[1] << " " << b[2] << endl;

    return 0;
}
