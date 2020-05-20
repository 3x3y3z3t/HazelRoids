#include "GameObject.h"
#include "ext\ExtensionFunctions.h"

#include "RoidsGame.h"
#include "Bullet.h"

namespace hzg
{
    GameObject::GameObject()
    {}

    void GameObject::Shoot()
    {
        Bullet* b = new Bullet();
        b->SetPosition(m_GunPosition);
        b->SetRotation(m_Rotation);
        b->SetMaxSpeed(1.0f + m_Speed);
        b->SetMaxLifetime(1.0f);

        RoidsGame::Get()->AddBullet(b);
        Reload();
    }

    bool GameObject::Collide(GameObject* _other)
    {
        if (m_Type == _other->m_Type)
            return false;

        float offsX = _other->m_Position.x - m_Position.x;
        float offsY = _other->m_Position.y - m_Position.y;

        // broad phase;
        if (offsX > (m_HitboxRadius + _other->m_HitboxRadius) || offsY > (m_HitboxRadius + _other->m_HitboxRadius))
        {
            return false;
        }

        float distance = glm::sqrt(glm::pow(offsX, 2.0f) + glm::pow(offsY, 2.0f));

        if (distance <= (m_HitboxRadius + _other->m_HitboxRadius))
        {
			float relative = m_HitboxRadius / (m_HitboxRadius + _other->m_HitboxRadius);
			float x = (m_Position.x + _other->m_Position.x) * relative;
			float y = (m_Position.y + _other->m_Position.y) * relative;
			m_CollisionPosition = { x, y };
			_other->m_CollisionPosition = { x, y };

            _other->Kill();
            Kill();
            return true;
        }

        return false;
    }

    void GameObject::Update(Hazel::Timestep _ts)
    {
        if (m_Accelerating > 0)
        {
            m_Speed += m_AccelerationRate * _ts;
        }
        else if (m_Accelerating < 0)
        {
            m_Speed -= m_AccelerationRate * 2.0f * _ts;
        }
        else
        {
            m_Speed -= m_AccelerationRate * _ts;
        }
        if (m_Speed > m_MaxSpeed) m_Speed = m_MaxSpeed;
        if (m_Speed < 0.0f) m_Speed = 0.0f;
        m_Accelerating = 0;

        if (m_Rotating > 0)
        {
            m_Rotation += m_RotationRate * _ts;
        }
        else if (m_Rotating < 0)
        {
            m_Rotation -= m_RotationRate * _ts;
        }
        if (m_Rotation > 180.0f) m_Rotation -= 360.0f;
        else if (m_Rotation < -179.0f) m_Rotation += 360.0f;
        m_Rotating = 0;

        m_CachedCos = glm::cos(glm::radians(m_Rotation));
        m_CachedSin = glm::sin(glm::radians(m_Rotation));

        float speedX = m_Speed * m_CachedCos * _ts;
        float speedY = m_Speed * m_CachedSin * _ts;

        m_Position = { m_Position.x + speedX, m_Position.y + speedY };

        if (m_Position.x > 1.7777777f)
            m_Position.x -= 1.7777777f * 2.0f;
        else if (m_Position.x < -1.7777777f)
            m_Position.x += 1.7777777f * 2.0f;
        if (m_Position.y > 1.0f)
            m_Position.y -= 2.0f;
        else if (m_Position.y < -1.0f)
            m_Position.y += 2.0f;

        m_RemainingReloadTime -= _ts;
        if (m_RemainingReloadTime < 0.0f) m_RemainingReloadTime = 0.0f;

        m_Lifetime += _ts;
        if (m_MaxLifetime > 0.0f && m_Lifetime >= m_MaxLifetime)
        {
            m_Dead = true;
        }
    }

    void GameObject::Render(bool _drawDummy)
    {
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

        Hazel::Renderer2D::DrawRotatedQuad(pos, { 0.005f, 0.005f }, m_Rotation, { 1.0f, 0.0f, 0.0f, 1.0f });

        #ifdef HZ_DEBUG
        // draw rotation;
        float rad = glm::radians(m_Rotation);
        Hazel::Renderer2D::DrawRotatedQuad({ pos.x + glm::cos(rad) * m_HitboxRadius * 0.5f, pos.y + glm::sin(rad) * m_HitboxRadius * 0.5f },
                                           { m_HitboxRadius, 0.005f }, m_Rotation, { 1.0f, 0.0f, 1.0f, 1.0f });
        // draw hitbox;
        #if 1
        float b = 1.0f;
        glm::vec4 color = { 0.9f, 0.1f, 0.1f, 0.7f };

        std::vector<glm::vec2> vertices;
        for (float deg = 0.0f; deg <= 360.0f; deg += 9.0f)
        {
            float px = glm::cos(glm::radians(deg + 13.0f)) * m_HitboxRadius;
            float py = glm::sin(glm::radians(deg + 13.0f)) * m_HitboxRadius;

            //float x = pX * m_Cached_cos_val - pY * m_Cached_sin_val;
            //float y = pX * m_Cached_sin_val + pY * m_Cached_cos_val;

            vertices.push_back({ pos.x + px, pos.y + py });
        }

        //for (int i = 0; i < vertices.size() - 1; ++i)
        //{
        //    ext::DrawLine(vertices[i], vertices[i + 1], color, b);
        //}
        //ext::DrawLine(vertices.back(), vertices.front(), color, b);

        ext::DrawCircle(pos, m_HitboxRadius, color, b);

        #endif
        #endif // HZ_DEBUG
    }
}
