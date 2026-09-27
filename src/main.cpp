#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>

int main() {
    int serverSocket = socket(AF_INET, SOCK_STREAM, 0);

    if (serverSocket == -1) {
        std::cerr << "Failed to create socket\n";
        return 1;
    }

    sockaddr_in serverAddress{};
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_addr.s_addr = INADDR_ANY;
    serverAddress.sin_port = htons(6379);

    if (bind(
            serverSocket,
            reinterpret_cast<sockaddr*>(&serverAddress),
            sizeof(serverAddress)
        ) == -1) {
        std::cerr << "Failed to bind\n";
        close(serverSocket);
        return 1;
    }

    if (listen(serverSocket, 10) == -1) {
        std::cerr << "Failed to listen\n";
        close(serverSocket);
        return 1;
    }

    std::cout << "Listening on port 6379...\n";

    int clientSocket = accept(serverSocket, nullptr, nullptr);

    if (clientSocket == -1) {
        std::cerr << "Failed to accept connection\n";
        close(serverSocket);
        return 1;
    }

    std::cout << "Client connected!\n";

    char buffer[1024];

    int bytesReceived = recv(clientSocket, buffer, sizeof(buffer) - 1, 0);

    if (bytesReceived > 0) {
        buffer[bytesReceived] = '\0';
        std::cout << "Received: " << buffer << '\n';
    } else {
        std::cerr << "Failed to receive data\n";
    }

    close(clientSocket);
    close(serverSocket);

    return 0;
}