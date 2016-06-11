#include <new>
#include <ostream>
#include <iostream>
#include <map>
#include <vector>

using namespace std;

template <typename T> struct MyAlloc {
    typedef T value_type;

    MyAlloc() {}
    template <typename U> MyAlloc(const MyAlloc<U>&) {}
    bool operator==(const MyAlloc&) const { return true; }
    bool operator!=(const MyAlloc&) const { return false; }

    T* allocate(const size_t n) const {
        cout << "MyAlloc<T>::allocate()" << endl;

        if (n == 0) {
            return nullptr;
        }

        if (n > static_cast<size_t>(-1) / sizeof(T)) {
            throw bad_array_new_length();
        }

        void* const pv = malloc(n * sizeof(T));

        if (!pv) {
            throw bad_alloc();
        }

        return static_cast<T*>(pv);
    }

    void deallocate(T* const p, size_t) const {
        cout << "MyAlloc<T>::deallocate()" << endl;
        free(p);
    }
};

template <typename T> using MyVector = vector<T, MyAlloc<T>>;

struct Noisy {
    Noisy() { cout << "default ctor" << endl; }
    Noisy(const Noisy&) { cout << "copy ctor" << endl; }
    Noisy& operator=(const Noisy&) {
        cout << "copy assign" << endl;
        return *this;
    }
    Noisy(Noisy&&) { cout << "move ctor" << endl; }
    Noisy& operator=(Noisy&&) {
        cout << "move assign" << endl;
        return *this;
    }
    ~Noisy() { cout << "dtor" << endl; }
};

struct NoisyInt {
    Noisy n;
    int i = 0;
    unsigned long long ull = 0;
};

void test0() {
    cout << "==Test0==" << endl;
    NoisyInt src;
    cout << endl;
    NoisyInt dst = move(src);
}

template <typename T, typename U> auto add(const T& t, const U& u) {
    return t + u;
};

void test1() {
    cout << "==Test1==" << endl;
    cout << add(11, 22) << endl;
    cout << add(string("meow"), "purr") << endl;
}

template <typename C> decltype(auto) zeroth(C& c) { return c[0]; }

void test2() {
    cout << "==Test2==" << endl;
    // decltype(auto) return types.
    vector<int> v = {100, 200, 300};
    ++zeroth(v);
    cout << v[0] << endl;

    // generic lambdas
    auto l = [](const auto& x, const auto& y) { return x + y; };
    cout << l(33, 44) << endl;
    cout << l("kitty", string("cat")) << endl;
}

const string& get_one(const map<int, string>& m) noexcept { return m.at(1); }

void test3() {
    cout << "==Test3==" << endl;
    // unconditional noexcept
    map<int, string> m;
    m[0] = "TOS";
    m[1] = "TNG";
    m[2] = "DS9";
    m[3] = "VOY";
    m[4] = "ENT";

    cout << get_one(m) << endl;
#ifdef PROGRAM_GO_BOOM
    map<int, string> m2;
    m2[4] = "A New Hope";
    m2[5] = "The Empire Strikes Back";
    m2[6] = "Return of the Jedi";
    cout << get_one(m2) << endl; // There is no Episode 1
#endif                           // PROGRAM_GO_BOOM
}

template <typename T, typename U> constexpr auto mult(const T& t, const U& u) {
    return t * u;
};

void test4() {
    cout << "==Test4==" << endl;
    static_assert(is_same<ratio<mult(2, 3), mult(5, 7)>, ratio<6, 35>>::value,
                  "BOOM");
}

struct X {
    void f() & { cout << "I'm an lvalue!" << endl; }
    void f() && { cout << "I'm an rvalue!" << endl; }
};

void test5() {
    cout << "==Test5==" << endl;
    // ref-qualifiers
    X x;
    x.f();
    X().f();
}

struct B {
    B() = delete;
    explicit B(const char*) { cout << "B(const char*)" << endl; }
    B(int, int) { cout << "B(int, int)" << endl; }
};

struct D : B {
    using B::B;
};

void test6() {
    cout << "==Test6==" << endl;
    // inheriting constructors
    D d1("meow");
    D d2(10, 20);

    // alignof/alignas
    cout << alignof(NoisyInt) << endl;
    alignas(NoisyInt) unsigned char bytes[sizeof(NoisyInt)];
    (void)bytes;

    // extended sizeof
    cout << sizeof(NoisyInt::i) << endl;

    // __func__
    cout << __func__ << endl;
}

int main() {
    { MyVector<int> v = {11, 22, 33}; }
    cout << "Done!" << endl;
    cout << endl;
    test0();
    cout << endl;
    test1();
    cout << endl;
    test2();
    cout << endl;
    test3();
    cout << endl;
    test4();
    cout << endl;
    test5();
    cout << endl;
    test6();
}
