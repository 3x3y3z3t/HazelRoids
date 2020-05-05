#pragma once
#include "GameObject.h"

namespace hzg
{
    class Bullet : public GameObject
    {


    public:
        Bullet();
        ~Bullet() = default;


        virtual void Update(Hazel::Timestep _ts) override;
        virtual void Render(bool _drawDummy = false) override;
    };
}
