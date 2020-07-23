#include "Bullet.h"
#include "ext\ExtensionFunctions.h"
#include "ext\ParticleSystem.h"

#include "RoidsGame.h"

namespace hzg
{
    Bullet::Bullet()
    {
        m_Type = GameObjectType::Bullet;
        m_Score = 10;
        m_AccelerationRate = 0.0f;
        m_HitboxRadius = 0.02f;
    }

    void Bullet::Update(Hazel::Timestep _ts)
    {
        if (DRAW_BULLET_TRAIL)
        {
            if (m_FrameCount % 2 == 0U)
            {
                ext::Particle* particle = new ext::Particle(ext::ParticleShape::Square);

                particle->SetPosition(m_Position);
                particle->SetRotation(m_Rotation - 180.0f + ext::RNG32::NextFloat(-10.0f, 10.0f));
                particle->SetSize(0.01f);
                particle->SetMaxLifetime(0.5f);
                particle->SetMaxSpeed(0.1f);
                particle->SetColor({ 1.0f, 1.0f, 1.0f, 1.0f });

                ext::ParticleSystem::AddParticle(particle);
            }
        }

        m_Speed = m_MaxSpeed;
        GameObject::Update(_ts);
    }

    void Bullet::Render(bool _drawDummy)
    {
        GameObject::Render(_drawDummy);

        auto pos = m_Position;
        if (_drawDummy)
        {
            float x = m_Position.x;
            float y = m_Position.y;
            if (m_Position.x > 1.7777777f - 0.25f)
                x = m_Position.x - 1.7777777f * 2.0f;
            else if (m_Position.x < -1.7777777f + 0.25f)
                x = m_Position.x + 1.7777777f * 2.0f;
            if (m_Position.y > 0.75f)
                y = m_Position.y - 2.0f;
            else if (m_Position.y < -0.75f)
                y = m_Position.y + 2.0f;

            if (x == m_Position.x && y == m_Position.y)
                return;

            pos = { x, y };
        }


        glm::vec2 size = { 0.04f, 0.005f };
        Hazel::Renderer2D::DrawRotatedQuad(pos, size, m_Rotation, { 0.9f, 0.9f, 0.9f, 1.0f });

    }
}
