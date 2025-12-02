#include "../include/Client.h"
#include <iostream>
#include <cstring>
#include <unistd.h>
#include <arpa/inet.h>
#include <thread>

Client::Client(const std::string& serverIP, int serverPort)
    : serverIP(serverIP), serverPort(serverPort), clientSocket(-1), isConnected(false) {
    memset(&serverAddr, 0, sizeof(serverAddr));
}

Client::~Client() {
    disconnect();
}

void Client::setupSocket() {
    clientSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (clientSocket < 0) {
        throw std::runtime_error("Failed to create socket");
    }

    std::cout << "[Client] Socket created successfully" << std::endl;
}

void Client::connectToServer() {
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(serverPort);

    if (inet_pton(AF_INET, serverIP.c_str(), &serverAddr.sin_addr) <= 0) {
        close(clientSocket);
        throw std::runtime_error("Invalid server IP address");
    }

    if (connect(clientSocket, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) < 0) {
        close(clientSocket);
        throw std::runtime_error("Failed to connect to server");
    }

    isConnected = true;
    std::cout << "[Client] Connected to server " << serverIP << ":" << serverPort << std::endl;
}

void Client::start() {
    try {
        setupSocket();
        connectToServer();

        std::thread receiveThread(&Client::receiveMessages, this);
        receiveThread.detach();

        std::cout << "[Client] Client started. Type messages to send (type 'quit' to exit):" << std::endl;

    } catch (const std::exception& e) {
        std::cerr << "[Client] Error: " << e.what() << std::endl;
        disconnect();
    }
}

void Client::sendMessage(const std::string& message) {
    if (!isConnected) {
        std::cerr << "[Client] Not connected to server" << std::endl;
        return;
    }

    if (send(clientSocket, message.c_str(), message.length(), 0) < 0) {
        std::cerr << "[Client] Failed to send message" << std::endl;
        disconnect();
    }
}

void Client::receiveMessages() {
    char buffer[1024];

    while (isConnected) {
        memset(buffer, 0, sizeof(buffer));
        int bytesRead = recv(clientSocket, buffer, sizeof(buffer) - 1, 0);

        if (bytesRead <= 0) {
            if (isConnected) {
                std::cout << "[Client] Disconnected from server" << std::endl;
                disconnect();
            }
            break;
        }

        buffer[bytesRead] = '\0';
        std::cout << buffer << std::endl;
    }
}

void Client::disconnect() {
    if (!isConnected) {
        return;
    }

    isConnected = false;

    if (clientSocket >= 0) {
        close(clientSocket);
        clientSocket = -1;
    }

    std::cout << "[Client] Disconnected" << std::endl;
}

bool Client::isClientConnected() const {
    return isConnected;
}
