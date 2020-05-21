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

		float remainingPercent = (m_MaxLifetime - m_Lifetime) / m_MaxLifetime;
		if (m_Shape == ParticleShape::Square)
		{
			Hazel::Renderer2D::DrawRotatedQuad(pos, glm::vec2(m_Size * remainingPercent), m_Rotation, m_Color);
			return;
		}

		if (m_Shape == ParticleShape::Circle)
		{
			constexpr float fragCount = 32;
			constexpr float oneFragDeg = 90.0f / fragCount;

			for (float i = 0.0f; i < fragCount; ++i)
				Hazel::Renderer2D::DrawRotatedQuad(pos, glm::vec2(m_Size), oneFragDeg * i, m_Color);

			return;
		}

		if (m_Shape == ParticleShape::Line)
		{
			float percent = m_Lifetime / minLifetime;
			float size = (percent < 1.0f) ? m_Size * percent : m_Size;
			float rad = glm::radians(m_Rotation);

			Hazel::Renderer2D::DrawRotatedQuad(pos, { size, remainingPercent * 0.01f }, m_Rotation, m_Color);

			return;
		}

	}
}
