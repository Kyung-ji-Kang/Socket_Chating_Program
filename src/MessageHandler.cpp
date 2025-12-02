#include "../include/MessageHandler.h"
#include <sstream>
#include <iomanip>
#include <algorithm>

std::string MessageHandler::formatMessage(const std::string& sender, const std::string& message) {
    std::string timestamp = getCurrentTimestamp();
    std::stringstream ss;
    ss << "[" << timestamp << "] " << sender << ": " << message;
    return ss.str();
}

std::string MessageHandler::getCurrentTimestamp() {
    time_t now = time(0);
    struct tm* timeinfo = localtime(&now);

    std::stringstream ss;
    ss << std::setfill('0')
       << std::setw(2) << timeinfo->tm_hour << ":"
       << std::setw(2) << timeinfo->tm_min << ":"
       << std::setw(2) << timeinfo->tm_sec;

    return ss.str();
}

bool MessageHandler::isValidMessage(const std::string& message) {
    if (message.empty()) {
        return false;
    }

    std::string trimmed = trimMessage(message);
    if (trimmed.empty()) {
        return false;
    }

    if (message.length() > 1024) {
        return false;
    }

    return true;
}

std::string MessageHandler::trimMessage(const std::string& message) {
    size_t start = message.find_first_not_of(" \t\n\r");
    if (start == std::string::npos) {
        return "";
    }

    size_t end = message.find_last_not_of(" \t\n\r");
    return message.substr(start, end - start + 1);
}

int MessageHandler::getMessageLength(const std::string& message) {
    return message.length();
}
