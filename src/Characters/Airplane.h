#ifndef AIRPLANE_H
#define AIRPLANE_H

#include "Character.h"
#include "Animation.h"

class Airplane: public Character
{
    public:
        Airplane(Properties* props);//dam bao cac thuoc tinh cua airplane

        virtual void Draw() override;
        virtual void Clean() override;
        virtual void Update(float dt);

    private:
        //int m_Row, m_Frame, m_FrameCount;
        //int m_AnimSpeed;

        Animation* m_Animation;
};

#endif // AIRPLANE_H
