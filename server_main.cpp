#include "include/Server.h"
#include <iostream>
#include <csignal>
#include <cstdlib>

Server* serverInstance = nullptr;

void signalHandler(int signal) {
    std::cout << "\n[Main] Shutting down server..." << std::endl;
    if (serverInstance) {
        serverInstance->stop();
    }
    exit(0);
}

int main(int argc, char* argv[]) {
    int port = 8080;

    if (argc > 1) {
        port = std::atoi(argv[1]);
        if (port <= 0 || port > 65535) {
            std::cerr << "Invalid port number. Using default port 8080." << std::endl;
            port = 8080;
        }
    }

    signal(SIGINT, signalHandler);
    signal(SIGTERM, signalHandler);

    std::cout << "========================================" << std::endl;
    std::cout << "   TCP/IP Socket Chat Server" << std::endl;
    std::cout << "========================================" << std::endl;
    std::cout << "Server will start on port: " << port << std::endl;
    std::cout << "Press Ctrl+C to stop the server" << std::endl;
    std::cout << "========================================\n" << std::endl;

    try {
        Server server(port);
        serverInstance = &server;

        server.start();

    } catch (const std::exception& e) {
        std::cerr << "[Main] Fatal error: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}
