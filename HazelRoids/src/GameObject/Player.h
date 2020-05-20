#pragma once
#include "GameObject.h"

namespace hzg
{
    class Player : public GameObject
    {

    public:
        Player();
        ~Player() = default;

		inline void Revive() { m_Dead = false; m_CollisionPosition = { 0.0f, 0.0f }; }

        virtual void Update(Hazel::Timestep _ts) override;
        virtual void Render(bool _drawDummy = false) override;
    };
}
