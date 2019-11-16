#include <iostream>
#include "ser_and_des.cpp"
#include <cassert>

using namespace std;

struct Data
{
    uint64_t a;
    bool b;
    uint64_t c;

    Data(uint64_t a1, bool b1, uint64_t c1)
    {
        a = a1;
        b = b1;
        c = c1;    
    }

    Error serialize(const Serializer& ser) const
    {
        return ser(a, b, c);
    }

    Error deserialize(Deserializer &des)
    {
        return des(des.GetIterOnSplitList(), a, b, c);
    }
};

int main()
{
    Data x(2, true, 2 );
    std::stringstream stream;
    Serializer serializer(stream);

    Error err = serializer.Save(x);
    assert(err == Error::NoError);

    Data y (0, false, 0 );

    Deserializer deserializer(stream);
    err = deserializer.Load(y);

    assert(deserializer.Load(y) == Error::NoError);

    //cout << x.a << ' '<< x.b << ' ' << x.c << endl;
    //cout << y.a << ' '<< y.b << ' ' << y.c << endl;
    assert(x.a == y.a);
    assert(x.b == y.b);
    assert(x.c == y.c);
    cout << "Done" << endl;
    return 0;
}
