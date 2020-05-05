#pragma once
#include <Hazel.h>

#include "GameObject\Player.h"
#include "GameObject\Bullet.h"

namespace hzg
{
    class RoidsGame : public Hazel::Layer
    {
    private:
        Hazel::OrthographicCameraController m_CameraController;

        static RoidsGame* s_Instance;

        float m_WorldTime = 0.0f;
        bool m_ShowDebugGui = false;

        Player* m_Player = nullptr;

        std::vector<GameObject*> m_Objects;
        std::vector<Bullet*> m_Bullets;

    private:
        RoidsGame();
    public:
        ~RoidsGame() = default;

    public:
        static RoidsGame* Create();
        inline static RoidsGame* Get() { if (s_Instance == nullptr) return Create(); return s_Instance; }

        void Init();

        void AddGameObject(GameObject* _object)
        {
            if (_object->GetType() == GameObjectType::Player || _object->GetType() == GameObjectType::None)
                return;

            if (_object->GetType() == GameObjectType::Bullet)
            {
                m_Bullets.push_back((Bullet*)_object);
                return;
            }

            m_Objects.push_back(_object);
        }
        void SpawnUFO(const glm::vec2& _position);
        void SpawnRoid(const glm::vec2& _position, unsigned int _size = 0U);

        inline Player* GetPlayer() const { return m_Player; }

        virtual void OnAttach() override;
        virtual void OnDetach() override;

        void OnUpdate(Hazel::Timestep _ts) override;
        virtual void OnImGuiRender() override;
        void OnEvent(Hazel::Event& _event) override;
    };
}