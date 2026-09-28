#include "network/server.hpp"

int main()
{
    Server server(5000);
    server.run();

    return 0;
}