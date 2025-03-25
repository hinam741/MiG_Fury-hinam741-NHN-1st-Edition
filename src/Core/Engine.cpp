#include "Engine.h"
#include<iostream>
Engine* Engine::s_Instance = nullptr;

Engine* Engine::GetInstance() {
    if (s_Instance == nullptr) {
        s_Instance = new Engine();
    }
    return s_Instance;
}

bool Engine::Init() {
    std::cout << "Engine initialized!" << std::endl;
    m_IsRunning = true;
    return true;
}

bool Engine::Clean() {
    std::cout << "Engine cleaned up!" << std::endl;
    m_IsRunning = false;
    return true;
}

void Engine::Quit() {
    std::cout << "Engine quitting..." << std::endl;
    m_IsRunning = false;
}

void Engine::Update() {
    std::cout << "Updating..." << std::endl;
}

void Engine::Render() {
    std::cout << "Rendering..." << std::endl;
}

void Engine::Events() {
    std::cout << "Handling events..." << std::endl;
}
