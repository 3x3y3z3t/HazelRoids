#pragma once
#include "GameObject.h"

namespace hzg
{
    class Bullet : public GameObject
    {
	private:
		unsigned int m_FrameCount = 0U;

    public:
        Bullet();
        ~Bullet() = default;

        virtual void Shoot() override {}

        virtual void Update(Hazel::Timestep _ts) override;
        virtual void Render(bool _drawDummy = false) override;
    };
}
