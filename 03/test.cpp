#include <iostream>
#include "matrix.h"
#include <cassert>

using namespace std;

template
<typename T> bool isConst(T &x) { return false; }

template
<typename T> bool isConst(T const &x) { return true; }

int main()
{
    Matrix m(3,5), a(3,5), b(3,5);
    const Matrix& ref_m = Matrix(3,5);
    m[1][2] = 10;
    m[2][4] = m[1][2] + 5;

    assert(m[1][2] == 10);
    assert(m[2][4] == 15);
    assert(isConst(ref_m[1][2]) == true);
    assert(isConst(m[1][2]) == false);
    assert(m.getColumns() == 5);
    assert(m.getRows() == 3);
    assert(m != a);
    assert(a == b);

    m *= 3;

    assert((m[1][2] == 30) && (m[2][4] == 45));
    cout << "done" << endl;
    return 0;
}
