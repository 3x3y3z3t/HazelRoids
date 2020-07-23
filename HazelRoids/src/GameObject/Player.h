#pragma once
#include "GameObject.h"

namespace hzg
{
    class Player : public GameObject
    {
    private:
        float m_MaxImmuneTime = 2.0f;
    public:
        Player();
        ~Player() = default;

        inline void Revive() { m_Dead = false; m_CollisionPosition = { 0.0f, 0.0f }; m_ImmuneTime = m_MaxImmuneTime; }

        virtual void Update(Hazel::Timestep _ts) override;
        virtual void Render(bool _drawDummy = false) override;
    };
}
