// from: http://stackoverflow.com/questions/1518534/multiple-output-operators

#include <iostream>

using namespace std;
class ostream_enum_wrapper_human
{
    public:
    ostream& out;
    ostream_enum_wrapper_human(std::ostream& _out) : out(_out){}

};

class ostream_enum_wrapper_int
{
    public:
    std::ostream& out;
    ostream_enum_wrapper_int(std::ostream& _out) : out(_out){}
};


enum T{zero,one,two};

struct human_readable{} HumanReadable;
ostream_enum_wrapper_human operator << (ostream& out, human_readable){
    return ostream_enum_wrapper_human(out);
}

struct print_int{} PrintInt;
ostream_enum_wrapper_int operator << (ostream& out, print_int){
    return ostream_enum_wrapper_int(out);
}


ostream& operator << (ostream_enum_wrapper_human out, T t)
{
    switch(t) {
        case zero: out.out << "zero"; break;
        case one: out.out << "one"; break;
        case two: out.out << "two"; break;
    }

    return out.out;
}

ostream& operator << (ostream_enum_wrapper_int out, T t)
{
    return out.out << static_cast<int>(t);
}

int main()
{
    cout << HumanReadable << zero << PrintInt << zero << HumanReadable << two;
}
