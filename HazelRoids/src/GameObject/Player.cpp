#include "Player.h"
#include "ext\ExtensionFunctions.h"

namespace hzg
{
    Player::Player()
        : GameObject()
    {
        m_Type = GameObjectType::Player;
        m_HitboxRadius = 0.05f;
    }

    void Player::Update(Hazel::Timestep _ts)
    {
        GameObject::Update(_ts);
    }

    void Player::Render(bool _drawDummy)
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

        m_Vertices.clear();

        constexpr float pointAngle = 30.0f;
        constexpr float ab = 0.25f;
        float ah = ab * glm::cos(glm::radians(pointAngle * 0.5f));
        float bh = ab * glm::sin(glm::radians(pointAngle * 0.5f));
        float ag = ah * 0.6666666f;
        float gh = ah * 0.3333333f;

        m_Vertices.push_back({ pos.x + +ag, pos.y + +0.0f });
        m_Vertices.push_back({ pos.x + -gh, pos.y + +bh });
        m_Vertices.push_back({ pos.x + -gh, pos.y + -bh });

        for (int i = 0; i < m_Vertices.size(); ++i)
        {
            glm::vec2& pt = m_Vertices[i];
            pt.x -= pos.x;
            pt.y -= pos.y;

            float x = pt.x * m_CachedCos - pt.y * m_CachedSin;
            float y = pt.x * m_CachedSin + pt.y * m_CachedCos;

            pt.x = x + pos.x;
            pt.y = y + pos.y;

            //m_Vertices[i] = pt;
        }
        m_GunPosition = m_Vertices[0];

        ext::DrawLine(m_Vertices[0], m_Vertices[1]);
        ext::DrawLine(m_Vertices[0], m_Vertices[2]);
        ext::DrawLine(m_Vertices[1], m_Vertices[2]);
    }
}
