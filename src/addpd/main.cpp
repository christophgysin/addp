#include <iostream>
#include <addp.h>

class addpd {
public:
    static std::string version()
    {
        return "0.1";
    }
};

int main(int argc, char* argv[])
{
    std::cout << "libaddp version: " << addp::version() << std::endl;
    std::cout << "addpd version:   " << addpd::version() << std::endl;

    return 0;
}
