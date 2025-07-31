#include "GameLoop.h"
#include "Core/Logger.h"

namespace Creative {

GameLoop::GameLoop() {
    // Constructor
}

GameLoop::~GameLoop() {
    // Destructor
}

void GameLoop::Start() {
    m_IsRunning = true;
    Logger::Info("GameLoop started.");
}

void GameLoop::Stop() {
    m_IsRunning = false;
    Logger::Info("GameLoop stopped.");
}

} // namespace Creative
