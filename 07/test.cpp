#include <iostream>
#include "my_vector.h"
#include <cassert>

using namespace std;

int main()
{
    Vector<int> v1;

    assert((v1.vec_size() == 0) && (v1.vec_capacity() == 0));

    v1.push_back(3);

    assert((v1.vec_size() == 1) && (v1.vec_capacity() == 2));
    
    v1.push_back(4);
    
    assert((v1.vec_size() == 2) && (v1.vec_capacity() == 2));

    v1.push_back(4);

    assert((v1.vec_size() == 3) && (v1.vec_capacity() == 4));
    
    assert((v1[0] == 3));
    assert((v1[1] == 4));
    assert((v1[2] == 4));
    
    //for (Vector<int>::iterator it = v1.begin(); it != v1.end(); it++)
    //    cout<< *it << endl;

    v1.pop_back();

    assert((v1.vec_size() == 2) && (v1.vec_capacity() == 4));
   
    v1.clear();
     
    assert((v1.vec_size() == 0) && (v1.vec_capacity() == 4));
    assert(v1.empty());

    v1.push_back(3);
    v1.reserve(5);

    assert((v1.vec_size() == 1) && (v1.vec_capacity() == 8));
    assert(v1[0] == 3);

    v1.push_back(1);
    v1.resize(1);
    
    assert((v1.vec_size() == 1) && (v1.vec_capacity() == 8));
    
    cout << "Done" << endl;

    return 0;
}

