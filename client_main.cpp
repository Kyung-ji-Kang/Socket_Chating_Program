#include "include/Client.h"
#include "include/MessageHandler.h"
#include <iostream>
#include <string>
#include <csignal>
#include <cstdlib>

Client* clientInstance = nullptr;

void signalHandler(int signal) {
    std::cout << "\n[Main] Disconnecting from server..." << std::endl;
    if (clientInstance) {
        clientInstance->disconnect();
    }
    exit(0);
}

int main(int argc, char* argv[]) {
    std::string serverIP = "127.0.0.1";
    int port = 8080;

    if (argc > 1) {
        serverIP = argv[1];
    }
    if (argc > 2) {
        port = std::atoi(argv[2]);
        if (port <= 0 || port > 65535) {
            std::cerr << "Invalid port number. Using default port 8080." << std::endl;
            port = 8080;
        }
    }

    signal(SIGINT, signalHandler);
    signal(SIGTERM, signalHandler);

    std::cout << "========================================" << std::endl;
    std::cout << "   TCP/IP Socket Chat Client" << std::endl;
    std::cout << "========================================" << std::endl;
    std::cout << "Connecting to: " << serverIP << ":" << port << std::endl;
    std::cout << "Press Ctrl+C to disconnect" << std::endl;
    std::cout << "========================================\n" << std::endl;

    try {
        Client client(serverIP, port);
        clientInstance = &client;

        client.start();

        std::string message;
        while (client.isClientConnected()) {
            std::cout << "You: ";
            if (!std::getline(std::cin, message)) {
                break;
            }

            if (message == "quit" || message == "exit") {
                std::cout << "[Client] Disconnecting..." << std::endl;
                break;
            }

            if (MessageHandler::isValidMessage(message)) {
                message = MessageHandler::trimMessage(message);
                client.sendMessage(message);
            } else {
                std::cout << "[Client] Invalid message (empty or too long)" << std::endl;
            }
        }

        client.disconnect();

    } catch (const std::exception& e) {
        std::cerr << "[Main] Fatal error: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}
