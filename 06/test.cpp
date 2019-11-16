#include <iostream>
#include "format.cpp"
#include <cassert>

using namespace std;

int main()
{
    auto text = format("{1}+{1}+{1} = {0}", 3, "one");
    assert(text == "one+one+one = 3");
    cout << "Done" << endl;
    return 0;
}
