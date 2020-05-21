#include "Player.h"
#include "ext\ExtensionFunctions.h"
#include "ext\ParticleSystem.h"

#include "RoidsGame.h"

namespace hzg
{
    Player::Player()
        : GameObject()
    {
        m_Type = GameObjectType::Player;
        m_HitboxRadius = 0.05f;

		m_ImmuneTime = m_MaxImmuneTime;


		// ;
		m_Vertices.reserve(3);
		m_Vertices.emplace_back(0.0f, 0.0f);
		m_Vertices.emplace_back(0.0f, 0.0f);
		m_Vertices.emplace_back(0.0f, 0.0f);
    }

    void Player::Update(Hazel::Timestep _ts)
    {
		if (DRAW_PLAYER_SHIP_THRUSTER_FLAME)
		{
			if (m_Accelerating > 0)
			{
				float x = (m_Vertices[2].x - m_Vertices[1].x) * 0.33333333f;
				float y = (m_Vertices[2].y - m_Vertices[1].y) * 0.33333333f;
				glm::vec2 thrusterPos[2] = {
					{ m_Vertices[1].x + x * 1.0f, m_Vertices[1].y + y * 1.0f },
					{ m_Vertices[1].x + x * 2.0f, m_Vertices[1].y + y * 2.0f }
				};

				for (unsigned int i = 0; i < 2; ++i)
				{
					ext::Particle* particle = new ext::Particle(ext::ParticleShape::Square);

					particle->SetPosition(thrusterPos[i]);
					particle->SetRotation(m_Rotation - 180.0f + ext::RNG32::NextFloat(-10.0f, 10.0f));
					particle->SetSize(ext::RNG32::NextFloat(0.005f, 0.015f));
					particle->SetMaxLifetime(ext::RNG32::NextFloat(0.4f, 0.6f));
					particle->SetMaxSpeed(ext::RNG32::NextFloat(0.4f, 0.6f));
					particle->SetColor({ 1.0f, 1.0f, 1.0f, 1.0f });

					ext::ParticleSystem::AddParticle(particle);
				}
			}
		}

        GameObject::Update(_ts);
    }

    void Player::Render(bool _drawDummy)
    {
		if (m_ImmuneTime > 0.0f)
		{
			if (m_FrameCount % 6 < 3U)
				return;
		}
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

        //m_Vertices.clear();

        constexpr float pointAngle = 30.0f;
        constexpr float ab = 0.25f;
        float ah = ab * glm::cos(glm::radians(pointAngle * 0.5f));
        float bh = ab * glm::sin(glm::radians(pointAngle * 0.5f));
        float ag = ah * 0.6666666f;
        float gh = ah * 0.3333333f;

        m_Vertices[0] = { pos.x + +ag, pos.y + +0.0f };
        m_Vertices[1] = { pos.x + -gh, pos.y + +bh };
        m_Vertices[2] = { pos.x + -gh, pos.y + -bh };

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
