#include "options.h"
#include "client.h"

int main(int argc, char* argv[])
{
    addpc::options options(argc, argv);
    addpc::client client(options);

    return client.run();
}
