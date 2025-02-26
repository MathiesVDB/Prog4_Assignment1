#pragma once
#include <glm.hpp>
#include <cmath>

#include "Component.h"

namespace dae
{
	class GameObject;
	class Transform final : public Component
	{
	public:
		enum class MovementPattern
		{
			None,
			Circle
		};

		void Update(float deltaTime) override;
		void SetMovementPattern(MovementPattern pattern){ m_MovementPattern = pattern; }

		const glm::vec3& GetPosition() const;
		void SetPosition(float x, float y, float z);
		void SetSpeed(float newSpeed);
	private:
		glm::vec3 m_Position{0, 0, 0};
		MovementPattern m_MovementPattern{ MovementPattern::None };
		float m_Time{ 0.0f };
		float m_Speed{ 70.0f };
	};
}
