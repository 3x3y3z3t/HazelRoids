#pragma once
#include "GameObject.h"

namespace hzg
{
    class UFO : public GameObject
    {
    public:
        UFO();
        ~UFO() = default;

        virtual void Shoot() override;

        virtual void Update(Hazel::Timestep _ts) override;
        virtual void Render(bool _drawDummy = false) override;
    };
}
