#include <iostream>
#include "big_numbers.h"
#include <cassert>

using namespace std;

int main()
{
    BigInt b = 10;
    BigInt c = -b;
    BigInt res = b - c;
    
    assert(((b - c) == 20) == true);
    assert(((b + c) == (-c - b)) == true);
    assert((b > 10) == false);
    assert((-b < 10) == true);
    assert((b >= 10) == true);
    assert((b <= 10) == true);
    assert((b == -c) == true);
    assert((b != c) == true);
    
    BigInt a = 100000*10000;
    cout << a << endl;
    for (int i = 0; i < 40; i++)
    {
        a = a + a;
        cout << a << endl;
    }
    return 0;
}
