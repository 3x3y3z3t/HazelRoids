#include "UFO.h"
#include "ext\ExtensionFunctions.h"

#include "RoidsGame.h"
#include "Bullet.h"

namespace hzg
{
    UFO::UFO()
    {
        m_Type = GameObjectType::UFO;
        m_Score = 5000;
        m_HitboxRadius = 0.06f;

        m_RotationRate = 0.0f;
    }

    void UFO::Shoot()
    {
        Bullet* b = new Bullet();
        b->SetPosition(m_GunPosition);
        b->SetRotation(m_Rotation);
        b->SetMaxSpeed(0.75f + m_Speed);
        b->SetMaxLifetime(1.0f);

        RoidsGame::Get()->AddGameObject(b);
        Reload();
    }

    void UFO::Update(Hazel::Timestep _ts)
    {
        m_GunPosition = { m_Position.x, m_Position.y - 0.04f };

        auto player = RoidsGame::Get()->GetPlayer();
        auto playerPos = player->GetPosition();
        auto playerRot = player->GetRotation();

        if (playerPos.x > 1.7777777f)
            playerPos.x -= 1.7777777f * 2.0f;
        else if (playerPos.x < -1.7777777f)
            playerPos.x += 1.7777777f * 2.0f;
        if (playerPos.y > 1.0f)
            playerPos.y -= 2.0f;
        else if (playerPos.y < -1.0f)
            playerPos.y += 2.0f;

        float rad = glm::atan((playerPos.y - m_Position.y), (playerPos.x - m_Position.x));
        m_Rotation = glm::degrees(rad);

        float distance = glm::distance(m_Position, playerPos);
        if (distance > 1.0f || m_Rotation < -150.0f || m_Rotation > -30.0f)
        {
            // try getting close and above;
            m_Accelerating = 1;
        }
        else
        {
            m_Accelerating = 0;
            if (m_Rotation >= -150.0f && m_Rotation < -30.0f)
            {
                if (IsReadyToShoot())
                {
                    Shoot();
                }
            }
        }

        GameObject::Update(_ts);
    }

    void UFO::Render(bool _drawDummy)
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

        m_Vertices.push_back({ pos.x + -0.07f, pos.y + +0.01f });
        m_Vertices.push_back({ pos.x + +0.07f, pos.y + +0.01f });
        m_Vertices.push_back({ pos.x + +0.10f, pos.y + -0.02f });
        m_Vertices.push_back({ pos.x + -0.10f, pos.y + -0.02f });
        m_Vertices.push_back({ pos.x + -0.06f, pos.y + -0.02f });
        m_Vertices.push_back({ pos.x + -0.05f, pos.y + -0.04f });
        m_Vertices.push_back({ pos.x + +0.05f, pos.y + -0.04f });
        m_Vertices.push_back({ pos.x + +0.06f, pos.y + -0.02f });

        float radius = 0.05f;
        for (float deg = 0.0f; deg <= 159.0f; deg += 5.0f)
        {
            float pX = glm::cos(glm::radians(deg + 13.0f)) * radius;
            float pY = glm::sin(glm::radians(deg + 13.0f)) * radius;
            m_Vertices.push_back({ pos.x + pX, pos.y + pY });
        }

        ext::DrawLine(m_Vertices[0], m_Vertices[1]);
        ext::DrawLine(m_Vertices[1], m_Vertices[2]);
        ext::DrawLine(m_Vertices[2], m_Vertices[3]);
        ext::DrawLine(m_Vertices[3], m_Vertices[0]);

        ext::DrawLine(m_Vertices[4], m_Vertices[5]);
        ext::DrawLine(m_Vertices[5], m_Vertices[6]);
        ext::DrawLine(m_Vertices[6], m_Vertices[7]);

        for (int i = 0; i + 7 < m_Vertices.size() - 2; ++i)
        {
            ext::DrawLine(m_Vertices[i + 8], m_Vertices[i + 9]);
        }
    }
}
