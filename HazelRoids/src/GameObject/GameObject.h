#pragma once
#include <Hazel.h>

namespace hzg
{
    enum class GameObjectType : uint8_t
    {
        None = 0,
        Player = 1,
        UFO = 2,
        Asteroid = 3,
        Bullet = 4
    };
    class GameObject
    {
    protected:
        GameObjectType m_Type = GameObjectType::None;
        int m_Score = 0;
        glm::vec2 m_Position = { 0.0f, 0.0f };
        float m_Rotation = 0.0f;

        float m_Speed = 0.0f;
        float m_MaxSpeed = 0.0f;
        float m_AccelerationRate = 0.0f;
        float m_RotationRate = 0.0f;

        glm::vec2 m_GunPosition = { 0.0f, 0.0f };
        float m_ReloadTime = 0.0f;
        float m_RemainingReloadTime = 0.0f;

        float m_Lifetime = 0.0f;
        float m_MaxLifetime = 0.0f;

        float m_HitboxRadius = 0.0f;
		glm::vec2 m_CollisionPosition = { 0.0f, 0.0f };

        int m_Accelerating = 0;
        int m_Rotating = 0;
        bool m_Dead = false;

        std::vector<glm::vec2> m_Vertices;
        float m_CachedSin = 0.0f;
        float m_CachedCos = 0.0f;

    protected:
        GameObject();
    public:
        virtual ~GameObject() = default;

        virtual void Shoot();
        virtual void Reload() { m_RemainingReloadTime = m_ReloadTime; }
        virtual void Kill() { m_Dead = true; }
        virtual bool Collide(GameObject* _other);

        inline bool IsDead() const { return m_Dead; }
        inline bool IsReadyToShoot() const { return m_RemainingReloadTime <= 0.0f; }
        inline GameObjectType GetType() const { return m_Type; }
        inline int GetScore() const { return m_Score; }
        inline const glm::vec2& GetPosition() const { return m_Position; }
        inline float GetRotation() const { return m_Rotation; }
		inline float GetHitboxRadius() const { return m_HitboxRadius; }
		inline const glm::vec2& GetCollisionPosition() const { return m_CollisionPosition; }
		inline int GetAccelerating() const { return m_Accelerating; }

        inline void SetPosition(const glm::vec2& _position) { m_Position = _position; }
        inline void SetRotation(float _rotation) { m_Rotation = _rotation; }
        inline void SetMaxSpeed(float _maxSpeed) { m_MaxSpeed = _maxSpeed; }
        inline void SetAccelerationRate(float _accelRate) { m_AccelerationRate = _accelRate; }
        inline void SetRotationRate(float _rotationRate) { m_RotationRate = _rotationRate; }
        inline void SetReloadTime(float _reloadTime) { m_ReloadTime = _reloadTime; }
        inline void SetMaxLifetime(float _maxLifetime) { m_MaxLifetime = _maxLifetime; }
        inline void SetAccelerating(int _accelerating) { m_Accelerating = _accelerating; }
        inline void SetRotating(int _rotating) { m_Rotating = _rotating; }

        virtual void Update(Hazel::Timestep _ts);
        virtual void Render(bool _drawDummy = false);
    };
}
