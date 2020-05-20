#pragma once
#include <Hazel.h>

namespace ext
{
	enum class ParticleShape
	{
		Square = 1,
		Circle = 2,
		Line = 3,
	};

	class Particle
	{
	private:
		ParticleShape m_Shape = ParticleShape::Square;
		glm::vec2 m_Position = { 0.0f, 0.0f };
		float m_Rotation = 0.0f;
		float m_Size = 0.0f;

		float m_Speed = 0.0f;
		float m_MaxSpeed = 0.0f;
		float m_AccelerationRate = 0.0f;
		float m_RotationRate = 0.0f;

		float m_Lifetime = 0.0f;
		float m_MaxLifetime = 0.0f;

		int m_Accelerating = 0;
		int m_Rotating = 0;
		bool m_Dead = false;

		glm::vec4 m_Color = { 0.0f, 0.0f, 0.0f, 0.0f };

		float m_CachedSin = 0.0f;
		float m_CachedCos = 0.0f;

	public:
		Particle(ParticleShape _shape = ParticleShape::Square);
		~Particle() = default;

	public:
		inline bool IsDead() const { return m_Dead; }

		inline void SetPosition(const glm::vec2& _position) { m_Position = _position; }
		inline void SetRotation(float _rotation) { m_Rotation = _rotation; }
		inline void SetSize(float _size) { m_Size = _size; }
		inline void SetMaxSpeed(float _maxSpeed) { m_MaxSpeed = _maxSpeed; }
		inline void SetAccelerationRate(float _accelRate) { m_AccelerationRate = _accelRate; }
		inline void SetRotationRate(float _rotationRate) { m_RotationRate = _rotationRate; }
		inline void SetMaxLifetime(float _maxLifetime) { m_MaxLifetime = _maxLifetime; }
		inline void SetAccelerating(int _accelerating) { m_Accelerating = _accelerating; }
		inline void SetRotating(int _rotating) { m_Rotating = _rotating; }
		inline void SetColor(glm::vec4 _color) { m_Color = _color; }

		void Update(Hazel::Timestep _ts);
		void Render(bool _drawDummy = false);
	};
}
