#pragma once
#include "GameObject.h"

namespace hzg
{
    class Asteroid : public GameObject
    {
    private:
        unsigned int m_Size = 1U;
        std::vector<float> m_VertexOffsets;

    public:
        Asteroid(unsigned int _size = 0U);
        ~Asteroid() = default;

        virtual void Shoot() override {}
        virtual void Kill() override;

        virtual void Update(Hazel::Timestep _ts) override;
        virtual void Render(bool _drawDummy = false) override;
    };
}
