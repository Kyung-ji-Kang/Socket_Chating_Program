#ifndef CLIENT_H
#define CLIENT_H

#include <string>
#include <sys/socket.h>
#include <netinet/in.h>

class Client {
private:
    int clientSocket;
    std::string serverIP;
    int serverPort;
    struct sockaddr_in serverAddr;
    bool isConnected;

    void setupSocket();
    void connectToServer();

public:
    Client(const std::string& serverIP, int serverPort);
    ~Client();

    void start();
    void sendMessage(const std::string& message);
    void receiveMessages();
    void disconnect();
    bool isClientConnected() const;
};

#endif
