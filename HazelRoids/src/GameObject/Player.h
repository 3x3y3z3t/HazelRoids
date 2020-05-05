#pragma once
#include "GameObject.h"

namespace hzg
{
    class Player : public GameObject
    {

    public:
        Player();
        ~Player() = default;



        virtual void Update(Hazel::Timestep _ts) override;
        virtual void Render(bool _drawDummy = false) override;
    };
}
