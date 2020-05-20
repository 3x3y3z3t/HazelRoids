#include <Hazel.h>
#include <Hazel/Core/EntryPoint.h>

#include "ext\ExtensionFunctions.h"
#include "ext\ParticleSystem.h"
#include "RoidsGame.h"

class Sandbox : public Hazel::Application
{
public:
	Sandbox()
	{
        ext::RNG32::Init();
		ext::ParticleSystem::Create();

        PushLayer(hzg::RoidsGame::Create());


	}

	~Sandbox()
	{
	}
};

Hazel::Application* Hazel::CreateApplication()
{
	return new Sandbox();
}
