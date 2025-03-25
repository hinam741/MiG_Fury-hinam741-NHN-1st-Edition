#include "Engine.h"
#include<iostream>
int main(int argc, char** argv) {
    if (!Engine::GetInstance()->Init()) {
        std::cerr << "Failed to initialize engine!" << std::endl;
        return -1;
    }

    while (Engine::GetInstance()->IsRunning()) {
        Engine::GetInstance()->Events();
        Engine::GetInstance()->Update();
        Engine::GetInstance()->Render();
    }

    Engine::GetInstance()->Clean();
    return 0;
}
