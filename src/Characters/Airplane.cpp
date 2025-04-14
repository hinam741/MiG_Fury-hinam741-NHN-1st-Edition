#include "Airplane.h"
#include "TextureManager.h" //include them trinh quan ly
#include "SDL.h"

Airplane::Airplane(Properties* props): Character(props)
{
    m_Animation = new Animation();
    m_Animation->SetProps(m_TextureID, 1, 6, 80, SDL_FLIP_HORIZONTAL);
}

void Airplane::Draw()
{
    m_Animation->Draw(m_Transform->X, m_Transform->Y, m_Width, m_Height);
}

void Airplane::Update(float dt)
{
    m_Animation->Update();
}
    //ctor

void Airplane::Clean()
{
    TextureManager::GetInstance()->Clean();
}
