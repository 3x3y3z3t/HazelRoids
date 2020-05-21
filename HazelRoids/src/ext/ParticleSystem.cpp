#include "ParticleSystem.h"

#include "ext\ExtensionFunctions.h"

namespace ext
{
	ParticleSystem* ParticleSystem::s_Instance = nullptr;

	ParticleSystem::ParticleSystem()
	{}

	ParticleSystem* ParticleSystem::Create()
	{
		if (s_Instance != nullptr)
		{
			HZ_WARN("ParticleSystem Instance has already been created!");
		}
		else
		{
			s_Instance = new ParticleSystem();
		}

		return s_Instance;
	}

	void ParticleSystem::UpdateParticles(Hazel::Timestep _ts)
	{
		auto& ps = ParticleSystem::Get()->m_Particles;
		for (size_t i = 0; i < ps.size(); ++i)
		{
			ps[i]->Update(_ts);
			if (ps[i]->IsDead())
			{
				ps.erase(ps.begin() + i);
			}
		}
		auto& es = ParticleSystem::Get()->m_Emitters;
		for (size_t i = 0; i < es.size(); ++i)
		{
			es[i]->Update(_ts);
			if (es[i]->IsDead())
			{
				es.erase(es.begin() + i);
			}
		}
	}

	void ParticleSystem::RenderParticles()
	{
		ParticleSystem* ps = Get();
		for (size_t i = 0; i < ps->m_Particles.size(); ++i)
		{
			ps->m_Particles[i]->Render();
			ps->m_Particles[i]->Render(true);
		}
	}

	ParticleEmitter::ParticleEmitter()
	{


	}
	
	void ParticleEmitter::Update(Hazel::Timestep _ts)
	{
		m_ElapsedLifetime += _ts;
		if (m_ElapsedLifetime >= m_EmitterLifetime)
		{
			m_Dead = true;
			return;
		}
		
		float deg = m_EmitDirection;
		if (m_EmitDirection == PARTICLE_EMITTER_EMIT_RANDOM_DIRECTION)
			deg = ext::RNG32::NextFloat(-179.0f, 180.0f);


		Particle* p = new Particle(m_ParticleShape);

		p->SetPosition(m_Position);
		p->SetRotationRate(m_ParticleRotationRate);
		p->SetRotation(deg);
		p->SetSize(0.07f);
		p->SetMaxLifetime(0.5f);
		p->SetColor({ 1.0f, 1.0f, 1.0f, 1.0f });
		p->SetMaxSpeed(0.5f);

		ParticleSystem::AddParticle(p);
	}
}
