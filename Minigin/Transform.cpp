#include "Transform.h"
#include "GameObject.h"

namespace dae
{
    void Transform::Update(float deltaTime)
    {
        if (m_MovementPattern != MovementPattern::Circle) return;

        auto ownerTransform = GetOwner()->GetComponent<Transform>();
        if (!ownerTransform) return;

        auto parent = GetOwner()->GetParent();
        if (!parent) return;

        auto parentTransform = parent->GetComponent<Transform>();
        if (!parentTransform) return;

        float angle = glm::radians(m_Speed * deltaTime);
        float cosA = glm::cos(angle);
        float sinA = glm::sin(angle);

        glm::mat3 rotationMatrix = glm::mat3(
            cosA, -sinA, 0.0f,
            sinA, cosA, 0.0f,
            0.0f, 0.0f, 1.0f
        );

        // Rotate the local position, so the object orbits its parent
        glm::vec3 relativePosition = ownerTransform->GetOwner()->GetLocalPosition();
        glm::vec3 rotatedRelativePosition = rotationMatrix * relativePosition;

        ownerTransform->GetOwner()->SetLocalPosition(rotatedRelativePosition);
    }


	void Transform::SetPosition(const float x, const float y, const float z)
	{
		GetOwner()->SetLocalPosition({ x, y, z });
	}

	void Transform::SetSpeed(float newSpeed)
	{
		m_Speed = newSpeed;
	}

	const glm::vec3& Transform::GetPosition() const
	{
		return GetOwner() ? GetOwner()->GetWorldPosition() : m_Position;
	}
}