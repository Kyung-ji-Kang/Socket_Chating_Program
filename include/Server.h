#ifndef SERVER_H
#define SERVER_H

#include <string>
#include <sys/socket.h>
#include <netinet/in.h>
#include <vector>

class Server {
private:
    int serverSocket;
    int port;
    struct sockaddr_in serverAddr;
    bool isRunning;
    std::vector<int> clientSockets;

    void setupSocket();
    void bindSocket();
    void listenForConnections();
    void handleClient(int clientSocket);

public:
    Server(int port);
    ~Server();

    void start();
    void stop();
    void broadcastMessage(const std::string& message, int senderSocket);
    int getPort() const;
    bool isServerRunning() const;
};

#endif
