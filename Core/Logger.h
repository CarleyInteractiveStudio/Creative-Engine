#ifndef CREATIVE_ENGINE_LOGGER_H
#define CREATIVE_ENGINE_LOGGER_H

#include <string>

namespace Creative {

class Logger {
public:
    static void Init();
    static void Info(const std::string& message);
    static void Warn(const std::string& message);
    static void Error(const std::string& message);

private:
    // Private constructor to prevent instantiation
    Logger() {}
};

} // namespace Creative

#endif //CREATIVE_ENGINE_LOGGER_H
