#include "Logger.h"
#include <iostream>
#include <chrono>
#include <iomanip> // For std::put_time
#include <ctime>   // For std::localtime

namespace Creative {

void Logger::Init() {
    // In the future, this could initialize file logging, etc.
    Info("Logger initialized.");
}

void Logger::Info(const std::string& message) {
    auto now = std::chrono::system_clock::now();
    auto in_time_t = std::chrono::system_clock::to_time_t(now);
    // std::localtime is not thread-safe. For a multi-threaded engine, this should be improved.
    std::cout << "[INFO] [" << std::put_time(std::localtime(&in_time_t), "%Y-%m-%d %X") << "] " << message << std::endl;
}

void Logger::Warn(const std::string& message) {
    auto now = std::chrono::system_clock::now();
    auto in_time_t = std::chrono::system_clock::to_time_t(now);
    std::cout << "[WARN] [" << std::put_time(std::localtime(&in_time_t), "%Y-%m-%d %X") << "] " << message << std::endl;
}

void Logger::Error(const std::string& message) {
    auto now = std::chrono::system_clock::now();
    auto in_time_t = std::chrono::system_clock::to_time_t(now);
    // Using std::cerr for errors is a good practice as it's unbuffered.
    std::cerr << "[ERROR] [" << std::put_time(std::localtime(&in_time_t), "%Y-%m-%d %X") << "] " << message << std::endl;
}

} // namespace Creative
