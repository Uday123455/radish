#include "network/server.hpp"
#include "parser/parser.hpp"
#include "storage/store.hpp"

#include <iostream>
#include <string>

#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>

Server::Server(int port)
    : port(port)
{
}

void Server::run()
{
    int server = socket(AF_INET, SOCK_STREAM, 0);

    if (server < 0) {
        std::cerr << "Failed to create socket\n";
        return;
    }

    sockaddr_in serverAddress{};

    serverAddress.sin_family = AF_INET;
    serverAddress.sin_addr.s_addr = INADDR_ANY;
    serverAddress.sin_port = htons(port);

    if (bind(
            server,
            reinterpret_cast<sockaddr*>(&serverAddress),
            sizeof(serverAddress)) < 0)
    {
        std::cerr << "Bind failed\n";
        close(server);
        return;
    }

    if (listen(server, 5) < 0) {
        std::cerr << "Listen failed\n";
        close(server);
        return;
    }

    std::cout << "Server listening on port " << port << '\n';

    int client = accept(server, nullptr, nullptr);

    if (client < 0) {
        std::cerr << "Accept failed\n";
        close(server);
        return;
    }

    Store store;

    char buffer[1024];

    while (true) {

        ssize_t bytesReceived =
            recv(client, buffer, sizeof(buffer) - 1, 0);

        if (bytesReceived <= 0) {
            break;
        }

        buffer[bytesReceived] = '\0';

        Command command = parseCommand(buffer);

        std::string response;

        if (command.name == "SET") {

            if (command.arguments.size() != 2) {
                response = "ERR wrong number of arguments\n";
            }
            else {
                store.set(
                    command.arguments[0],
                    command.arguments[1]
                );

                response = "OK\n";
            }
        }
        else if (command.name == "GET") {

            if (command.arguments.size() != 1) {
                response = "ERR wrong number of arguments\n";
            }
            else {
                const auto value = store.get(command.arguments[0]);
                response = value ? *value + "\n" : "(nil)\n";
            }
        }
        else if (command.name == "DEL") {

            if (command.arguments.size() != 1) {
                response = "ERR wrong number of arguments\n";
            }
            else {
                store.del(command.arguments[0]);
                response = "OK\n";
            }
        }
        else {
            response = "ERR unknown command\n";
        }

        send(client, response.c_str(), response.size(), 0);
    }

    close(client);
    close(server);
}