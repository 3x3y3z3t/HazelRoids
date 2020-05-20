#include "Particle.h"

namespace ext
{
	float minLifetime = 0.0f;

	Particle::Particle(ParticleShape _shape)
		: m_Shape(_shape)
	{}


	void Particle::Update(Hazel::Timestep _ts)
	{
		m_Lifetime += _ts;
		if (m_Lifetime > m_MaxLifetime)
		{
			m_Dead = true;
			return;
		}

		minLifetime = m_MaxLifetime * 0.5f;


		m_Speed = m_MaxSpeed;
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

	}

	void Particle::Render(bool _drawDummy)
	{
		if (m_Shape == ParticleShape::Square)
		{
			Hazel::Renderer2D::DrawRotatedQuad(m_Position, glm::vec2(m_Size), m_Rotation, m_Color);
			return;
		}

		if (m_Shape == ParticleShape::Circle)
		{
			constexpr float fragCount = 32;
			constexpr float oneFragDeg = 90.0f / fragCount;

			for (float i = 0.0f; i < fragCount; ++i)
				Hazel::Renderer2D::DrawRotatedQuad(m_Position, glm::vec2(m_Size), oneFragDeg * i, m_Color);

			return;
		}

		if (m_Shape == ParticleShape::Line)
		{
			float percent = m_Lifetime / minLifetime;
			float size = (percent < 1.0f) ? m_Size * percent : m_Size;
			float rad = glm::radians(m_Rotation);

			Hazel::Renderer2D::DrawRotatedQuad(m_Position, { size, 0.005f }, m_Rotation, m_Color);

			return;
		}

	}
}
