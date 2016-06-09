#include <functional>
#include <algorithm>
#include <string>
#include <vector>
#include <ostream>
#include <iostream>

using namespace std;

void meow() { cout << "meow!" << endl; }
void purr() { cout << "purr!" << endl; }

void woof(void (*myfp)()) {
    // Dereference function pointer and call.
    // (* fp)()
    // Syntactic sugar.
    myfp();
}

struct X {
    int meow() { return 11; }
    int purr() { return 22; }
    int woof(int n) const { return n * 33; }

    int a;
    int b;
};

bool compare_length(const string& l, const string& r) {
    return l.size() < r.size();
}

class Emphasize {
  public:
    explicit Emphasize(const string& s) : _str(s) {}
    string operator()(const string& input) const { return input + _str; }

  private:
    string _str;
};

int main() {
    for (int i = 0; i < 10; ++i) {
        if (i % 2 == 0) {
            meow();
        }
    }
    cout << endl;

    // A function will decay into a function pointer.
    // void (* fp)() = &meow;
    void (*fp)() = meow;
    woof(fp);

    X x = {100, 200};

    int X::*pmd = &X::a;
    cout << x.*pmd << endl;
    X* p = &x;
    cout << p->*pmd << endl;

    int (X::*pmf)() = &X::purr;
    int (X::*pmf2)(int) const = &X::woof;
    auto pmf3 = &X::woof;
    cout << (x.*pmf)() << endl;
    cout << (x.*pmf2)(5) << endl;
    cout << (x.*pmf3)(1) << endl;
    cout << endl;

    vector<string> v{"cat", "dog", "ox", "kitten", "puppy"};
    sort(v.begin(), v.end(), compare_length);
    // transform(v.begin(), v.end(), v.begin(), Emphasize("!!"));

    auto myLambda = [](const string& s) { return s + "!!!"; };
    string suffix = "!";
    int n = 0;
    auto myLambda2 = [=](const string& s) mutable {
        ++n;
        return s + suffix + to_string(n);
    };
    suffix = "SOMETHING";
    transform(v.begin(), v.end(), v.begin(), myLambda2);

    cout << "Value of n: " << n << endl;

    for (const auto& e : v) {
        cout << e << endl;
    }

    cout << "Bye!" << endl;
    return 0;
}
