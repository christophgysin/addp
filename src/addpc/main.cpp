#include <cctype>
#include <iostream>

#include "version.h"
#include "options.h"
#include "client.h"

int main(int argc, char* argv[])
{
    addpc::options options(argc, argv);

    if(options.version())
    {
        std::cout << ADDPC_VERSION << std::endl;
        return 0;
    }

    addpc::client client(options);
    return client.run();
}
