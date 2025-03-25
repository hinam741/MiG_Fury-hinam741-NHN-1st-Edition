#ifndef ENGINE_H
#define ENGINE_H

#include <iostream>

class Engine {
public:
    static Engine* GetInstance();

    bool Init();
    bool Clean();
    void Quit();

    void Update();
    void Render();
    void Events();

    inline bool IsRunning() { return m_IsRunning; }

private:
    Engine() : m_IsRunning(false) {}
    static Engine* s_Instance;
    bool m_IsRunning;
};

#endif // ENGINE_H
