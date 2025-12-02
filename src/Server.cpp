#include "../include/Server.h"
#include <iostream>
#include <cstring>
#include <unistd.h>
#include <arpa/inet.h>
#include <thread>
#include <algorithm>

Server::Server(int port) : port(port), serverSocket(-1), isRunning(false) {
    memset(&serverAddr, 0, sizeof(serverAddr));
}

Server::~Server() {
    stop();
}

void Server::setupSocket() {
    serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (serverSocket < 0) {
        throw std::runtime_error("Failed to create socket");
    }

    int opt = 1;
    if (setsockopt(serverSocket, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) < 0) {
        close(serverSocket);
        throw std::runtime_error("Failed to set socket options");
    }

    std::cout << "[Server] Socket created successfully" << std::endl;
}

void Server::bindSocket() {
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = INADDR_ANY;
    serverAddr.sin_port = htons(port);

    if (bind(serverSocket, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) < 0) {
        close(serverSocket);
        throw std::runtime_error("Failed to bind socket");
    }

    std::cout << "[Server] Socket bound to port " << port << std::endl;
}

void Server::listenForConnections() {
    if (listen(serverSocket, 5) < 0) {
        close(serverSocket);
        throw std::runtime_error("Failed to listen on socket");
    }

    std::cout << "[Server] Listening for connections..." << std::endl;
}

void Server::handleClient(int clientSocket) {
    char buffer[1024];

    while (isRunning) {
        memset(buffer, 0, sizeof(buffer));
        int bytesRead = recv(clientSocket, buffer, sizeof(buffer) - 1, 0);

        if (bytesRead <= 0) {
            std::cout << "[Server] Client disconnected (socket: " << clientSocket << ")" << std::endl;
            break;
        }

        buffer[bytesRead] = '\0';
        std::cout << "[Server] Received: " << buffer << std::endl;

        broadcastMessage(buffer, clientSocket);
    }

    close(clientSocket);

    auto it = std::find(clientSockets.begin(), clientSockets.end(), clientSocket);
    if (it != clientSockets.end()) {
        clientSockets.erase(it);
    }
}

void Server::start() {
    try {
        setupSocket();
        bindSocket();
        listenForConnections();

        isRunning = true;
        std::cout << "[Server] Server started successfully on port " << port << std::endl;

        while (isRunning) {
            struct sockaddr_in clientAddr;
            socklen_t clientLen = sizeof(clientAddr);

            int clientSocket = accept(serverSocket, (struct sockaddr*)&clientAddr, &clientLen);

            if (clientSocket < 0) {
                if (isRunning) {
                    std::cerr << "[Server] Failed to accept connection" << std::endl;
                }
                continue;
            }

            clientSockets.push_back(clientSocket);
            std::cout << "[Server] New client connected (socket: " << clientSocket << ")" << std::endl;

            std::thread clientThread(&Server::handleClient, this, clientSocket);
            clientThread.detach();
        }
    } catch (const std::exception& e) {
        std::cerr << "[Server] Error: " << e.what() << std::endl;
        stop();
    }
}

void Server::stop() {
    if (!isRunning) {
        return;
    }

    isRunning = false;

    for (int clientSocket : clientSockets) {
        close(clientSocket);
    }
    clientSockets.clear();

    if (serverSocket >= 0) {
        close(serverSocket);
        serverSocket = -1;
    }

    std::cout << "[Server] Server stopped" << std::endl;
}

void Server::broadcastMessage(const std::string& message, int senderSocket) {
    std::string formattedMsg = "[Client " + std::to_string(senderSocket) + "]: " + message;

    for (int clientSocket : clientSockets) {
        if (clientSocket != senderSocket) {
            send(clientSocket, formattedMsg.c_str(), formattedMsg.length(), 0);
        }
    }
}

int Server::getPort() const {
    return port;
}

bool Server::isServerRunning() const {
    return isRunning;
}
