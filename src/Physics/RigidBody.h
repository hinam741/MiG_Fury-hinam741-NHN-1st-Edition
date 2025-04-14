#ifndef RIGIDBODY_H
#define RIGIDBODY_H

#include "Vector2D.h"

//define const value
#define UNI_MASS 1.0f
#define GRAVITY 9.8f

class RigidBody
{
    public:
        RigidBody() {
            m_Mass = UNI_MASS;
            m_Gravity = GRAVITY;
        }
        //set mass and gravity
        inline void SetMass(float mass)(m_Mass = mass;)
        inline void SetFravity(float gravity)(m_Gravity = gravity;)

        //Force
        inline void ApplyForce(Vector2D F){m_Force = F;}
        inline void ApplyForceX (float Fx){m_Force.X = Fx;}
        inline void ApplyForceY (float Fy){m_Force.Y = Fy;}

    private:
        float m_Mass;//khối lượng
        float m_Gravity;//trọng lực

        Vector2D m_Force;
        Vector2D m_Friction;

        Vector2D m_Position;
        Vector2D m_Velocity;//vector vận tốc
        Vector2D m_Accelaration;//vector gia tốc
};

#endif // RIGIDBODY_H
