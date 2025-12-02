#ifndef MESSAGE_HANDLER_H
#define MESSAGE_HANDLER_H

#include <string>
#include <ctime>

class MessageHandler {
public:
    static std::string formatMessage(const std::string& sender, const std::string& message);
    static std::string getCurrentTimestamp();
    static bool isValidMessage(const std::string& message);
    static std::string trimMessage(const std::string& message);
    static int getMessageLength(const std::string& message);
};

#endif
