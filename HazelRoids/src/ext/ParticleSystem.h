#pragma once
#include <Hazel.h>

#include "Particle.h"

namespace ext
{
	class ParticleEmitter;

	class ParticleSystem
	{
		static ParticleSystem* s_Instance;

		std::vector<Particle*> m_Particles;
		std::vector<ParticleEmitter*> m_Emitters;

	private:
		ParticleSystem();
	public:
		~ParticleSystem() = default;

		static ParticleSystem* Create();
		inline static ParticleSystem* Get() { if (s_Instance == nullptr) return Create(); return s_Instance; }

		static void AddParticle(Particle* _particle) { Get()->m_Particles.insert(Get()->m_Particles.cbegin(), _particle); }
		static void AddEmitter(ParticleEmitter* _emitter) { Get()->m_Emitters.push_back(_emitter); }

		static void UpdateParticles(Hazel::Timestep _ts);
		static void RenderParticles();
	};

	class ParticleEmitter
	{
		#define PARTICLE_EMITTER_EMIT_RANDOM_DIRECTION 1351249.0f // just a non-meaning number;
	private:
		glm::vec2 m_Position = { 0.0f, 0.0f };
		float m_EmitDirection = 0.0f;
		float m_EmitterLifetime = 0.0f;
		float m_EmitInterval = 0.0f;

		ParticleShape m_ParticleShape = ParticleShape::Square;
		float m_ParticleSize = 0.0f;
		float m_ParticleSpeed = 0.0f;
		float m_ParticleAccelerationRate = 0.0f;
		float m_ParticleRotationRate = 0.0f;
		float m_ParticleLifetime = 0.0f;

		bool m_Dead = false;

		float m_ElapsedLifetime = 0.0f;
		float m_RemainingInterval = 0.0f;

	public:
		ParticleEmitter();
		~ParticleEmitter() = default;

		inline bool IsDead() const { return m_Dead; }

		inline void SetPosition(glm::vec2 _position) { m_Position = _position; }
		inline void SetEmitDirection(float _direction) { m_EmitDirection = _direction; }
		inline void SetEmitterLifetime(float _lifetime) { m_EmitterLifetime = _lifetime; }

		inline void SetParticleShape(ParticleShape _shape) { m_ParticleShape = _shape; }

		void Update(Hazel::Timestep _ts);
	};
}
