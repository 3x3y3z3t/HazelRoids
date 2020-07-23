#include "ExtensionFunctions.h"

#include "glm\gtc\constants.hpp"

namespace ext
{
    std::mt19937 RNG32::s_Engine;

    void DrawLine(const glm::vec2& _startPoint, const glm::vec2& _endPoint, const glm::vec4& _color, float _borderThickness)
    {
        if (_borderThickness < 1.0f) _borderThickness = 1.0f;

        glm::vec2 center = { (_endPoint.x + _startPoint.x) * 0.5f, (_endPoint.y + _startPoint.y) * 0.5f };
        float length = glm::distance(_startPoint, _endPoint);

        float angle = glm::degrees(glm::atan(_endPoint.y - _startPoint.y, _endPoint.x - _startPoint.x));

        Hazel::Renderer2D::DrawRotatedQuad(center, { length, _borderThickness * 0.003f }, angle, _color);
    }

    void DrawCircle(const glm::vec2& _centerPoint, float _radius, const glm::vec4& _color, float _borderThickness)
    {
        DrawArc(_centerPoint, _radius, -179.0f, 180.0f, _color, _borderThickness);
    }

    void DrawArc(const glm::vec2& _centerPoint, float _radius, float _startAngle, float _endAngle, const glm::vec4& _color, float _borderThickness)
    {
        if (_radius <= 0.0f) return;
        if (_startAngle == _endAngle) return;
        if (_borderThickness < 1.0f) _borderThickness = 1.0f;

        constexpr int maxLineCount = 32;
        constexpr float alpha = glm::pi<float>() * 2.0f / maxLineCount;
        constexpr float halfAlpha = alpha * 0.5f;
        float width = glm::sin(alpha) * _radius * 2.0f;

        float start = 0.0f;
        float end = 0.0f;
        if (_startAngle < _endAngle)
        {
            start = glm::radians(_startAngle);
            end = glm::radians(_endAngle);
        }
        else
        {
            start = glm::radians(_endAngle);
            end = glm::radians(_startAngle);
        }
        //start = _startAngle;
        //end = _endAngle;

        float arc = end - start;
        int lineCount = (int)(arc / alpha) + 1;

        for (int i = 0; i < lineCount; ++i)
        {
            float angle = start - alpha + alpha * i;
            float x = _centerPoint.x + glm::cos(angle) * _radius;
            float y = _centerPoint.y + glm::sin(angle) * _radius;
            Hazel::Renderer2D::DrawRotatedQuad({ x, y }, { _borderThickness * 0.005f, width }, glm::degrees(angle), _color);
        }
    }
}
