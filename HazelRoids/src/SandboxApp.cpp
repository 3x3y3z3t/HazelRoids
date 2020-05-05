#include <Hazel.h>
#include <Hazel/Core/EntryPoint.h>

#include "ext\ExtensionFunctions.h"
#include "RoidsGame.h"

class Sandbox : public Hazel::Application
{
public:
	Sandbox()
	{
        ext::RNG32::Init();

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
