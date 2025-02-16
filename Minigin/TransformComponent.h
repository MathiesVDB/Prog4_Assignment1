#pragma once
#include "Component.h"
#include <glm.hpp>
#include <vec3.hpp>

class TransformComponent final : public Component
{
public:
    TransformComponent() = default;
    ~TransformComponent() override = default;

    void Update(float deltaTime) override { (void)deltaTime; }
    void Render() const override {}

    const glm::vec3& GetPosition() const { return m_Position; }
    void SetPosition(const glm::vec3& position) { m_Position = position; }

private:
    glm::vec3 m_Position{ 0.0f, 0.0f, 0.0f };
};
