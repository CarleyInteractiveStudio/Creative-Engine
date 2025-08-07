#pragma once

#include <iostream>
#include <string>
#include <memory>

// This is a basic logger. In a real engine, this would be far more complex,
// likely using a library like spdlog and allowing for different sinks (file, console, etc.).
// For now, we'll just wrap std::cout.

namespace Creative {

class Log
{
public:
    static void Init();

    // Core Engine Logger
    static void Core_Trace(const std::string& message) { std::cout << "[CORE TRACE]: " << message << std::endl; std::cout.flush(); }
    static void Core_Info(const std::string& message)  { std::cout << "[CORE INFO]: " << message << std::endl; std::cout.flush(); }
    static void Core_Warn(const std::string& message)  { std::cout << "[CORE WARN]: " << message << std::endl; std::cout.flush(); }
    static void Core_Error(const std::string& message) { std::cerr << "[CORE ERROR]: " << message << std::endl; std::cerr.flush(); }

    // Client/Game Logger
    static void Trace(const std::string& message) { std::cout << "[APP TRACE]: " << message << std::endl; std::cout.flush(); }
    static void Info(const std::string& message)  { std::cout << "[APP INFO]: " << message << std::endl; std::cout.flush(); }
    static void Warn(const std::string& message)  { std::cout << "[APP WARN]: " << message << std::endl; std::cout.flush(); }
    static void Error(const std::string& message) { std::cerr << "[APP ERROR]: " << message << std::endl; std::cerr.flush(); }
};

} // namespace Creative
