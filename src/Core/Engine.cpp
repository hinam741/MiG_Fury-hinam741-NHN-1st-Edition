//checked
#include "Engine.h"
#include "TextureManager.h"
#include "Airplane.h"

Engine* Engine::s_Instance = nullptr;
Airplane* player = nullptr;

bool Engine::Init()
{
   if(SDL_Init(SDL_INIT_VIDEO) != 0 && IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG) != 0){
    SDL_Log("Failed to initialize SDL: %s", SDL_GetError());
    return false;
   }
   //create window
   m_Window = SDL_CreateWindow("MiG Fury", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_HEIGHT, SCREEN_HEIGHT, 0);//0 for fullscreen
   if(m_Window == nullptr){
    SDL_Log("Failed to initialize Window: %s", SDL_GetError());
    return false;
   }

   m_Renderer = SDL_CreateRenderer(m_Window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
   if(m_Renderer == nullptr){
    SDL_Log("Failed to initialize Renderer: %s", SDL_GetError());
    return false;
   }

   TextureManager::GetInstance()->Load("player", "assets/mig21_pixels_2.png");
   player = new Airplane(new Properties("player", 100, 200, 224, 48));

   Transform tf;
   tf.Log();

}

void Engine::Update()
{
    player->Update(0);//(time)
}

void Engine::Render()
{
    SDL_SetRenderDrawColor(m_Renderer, 124, 218, 234, 255); //draw color for window
    SDL_RenderClear(m_Renderer);

    player->Draw();
    SDL_RenderPresent(m_Renderer);
}

void Engine::Events()
{
    SDL_Event event;
    SDL_PollEvent(&event);
    switch(event.type){
    case SDL_QUIT:
        Quit();
        break;
    }
}

bool Engine::Clean()
{
    TextureManager::GetInstance()->Clean();
    SDL_DestroyRenderer(m_Renderer);
    SDL_DestroyWindow(m_Window);
    IMG_Quit();
    SDL_Quit();
}

void Engine::Quit()
{
    m_IsRunning = false;
}
