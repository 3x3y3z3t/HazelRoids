#pragma once
#include <Hazel.h>
#include <random>

/** This contains all extension functions/classes/etc..
 *  which is currently not yet implemented in Hazel.
 */
namespace ext
{
    class RNG32
    {
    private:
        static std::mt19937 s_Engine;

    public:
        inline static void Init(unsigned int _seed = 0U)
        {
            if (_seed == 0U)
                _seed = std::random_device()();
            s_Engine.seed(_seed);
        }

        template <typename T = int>
        inline static T NextInt(T _lower = 0, T _upper = std::numeric_limits<T>::max())
        {
            if (_lower > _upper)
                return 0;
            return std::uniform_int_distribution<T>(_lower, _upper)(s_Engine);
        }

        template <typename T = float>
        inline static T NextFloat(T _lower = (T)0, T _upper = (T)1)
        {
            if (_lower > _upper)
                return 0.0f;
            return std::uniform_real_distribution<T>(_lower, _upper)(s_Engine);
        }
    };

    void DrawLine(const glm::vec2& _startPoint, const glm::vec2& _endPoint, const glm::vec4& _color = { 1.0f, 1.0f, 1.0f, 1.0f }, float _borderThickness = 1.0f);
    void DrawCircle(const glm::vec2& _centerPoint, float _radius, const glm::vec4& _color = { 1.0f, 1.0f, 1.0f, 1.0f }, float _borderThickness = 1.0f);
    void DrawArc(const glm::vec2& _centerPoint, float _radius, float _startAngle, float _endAngle, const glm::vec4& _color = { 1.0f, 1.0f, 1.0f, 1.0f }, float _borderThickness = 1.0f);
}
