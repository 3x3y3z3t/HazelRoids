#include "Asteroid.h"
#include "ext\ExtensionFunctions.h"

#include "RoidsGame.h"

namespace hzg
{
    Asteroid::Asteroid(unsigned int _size)
    {
        m_Type = GameObjectType::Asteroid;
        m_AccelerationRate = 0.0f;

        if (_size == 0U)
        {
			_size = 1U;
        }
        m_Size = _size;
        m_Score = 100 * (6 - m_Size);
        m_HitboxRadius = 0.04f * m_Size;

        float b = 0.4f;
        for (int i = 0; i < 16; ++i)
        {
            m_VertexOffsets.push_back(ext::RNG32::NextFloat(-b, b));
            //b = ext::RNG32::NextFloat(0.0f, 0.4f);
            //if (i % 2 == 0)
            //    m_VertexOffsets.push_back(b);
            //else
            //    m_VertexOffsets.push_back(-b);
        }
    }

    void Asteroid::Kill()
    {
        if (m_Size > 1U)
        {
            RoidsGame::Get()->SpawnRoid(m_Position, m_Size - 1U);
            RoidsGame::Get()->SpawnRoid(m_Position, m_Size - 1U);
        }
        GameObject::Kill();
    }

    void Asteroid::Update(Hazel::Timestep _ts)
    {
        m_Speed = m_MaxSpeed;
        GameObject::Update(_ts);
    }

    void Asteroid::Render(bool _drawDummy)
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

        float dStep = 360.0f / m_VertexOffsets.size();
        float deg = 0.0f;
        for (size_t i = 0; i < m_VertexOffsets.size(); ++i)
        {
            float c = glm::cos(glm::radians(deg));
            float s = glm::sin(glm::radians(deg));
            glm::vec2 v = { m_HitboxRadius * (1.0f + m_VertexOffsets[i]) * c, m_HitboxRadius * (1.0f + m_VertexOffsets[i]) * s };
            m_Vertices.push_back({ pos.x + v.x, pos.y + v.y });
            deg += dStep;
        }

        for (int i = 0; i < m_Vertices.size() - 1; ++i)
        {
            ext::DrawLine(m_Vertices[i], m_Vertices[i + 1]);
        }
        ext::DrawLine(m_Vertices.back(), m_Vertices.front());
    }
}
