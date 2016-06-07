#include <ios>
#include <ostream>
#include <iostream>

using namespace std;

int main() {
    signed char sc = -1;
    int i = 255;
    unsigned long ul = 0xFFFFFFFFFFFFFFFFUL;

    unsigned char x = 250;
    unsigned char y = 200;

    cout << boolalpha;
    cout << "signed char -1 == int 255? " << (sc == i) << endl;
    cout << "signed char -1 == unsigned long 0xFFFFFFFFFFFFFFFF? " << (sc == ul)
         << endl;
    // These short types immediately get widened to int during addition.
    cout << (x + y) << endl;

    return 0;
}
