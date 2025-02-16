#pragma once
#include <vector>
#include <memory>
#include <typeindex>
#include <unordered_map>
#include "Component.h"

namespace dae
{
	class GameObject final
	{
	public:
		GameObject()  = default;
		~GameObject() = default;
		GameObject(const GameObject& other)				= delete;
		GameObject(GameObject&& other)					= delete;
		GameObject& operator=(const GameObject& other)	= delete;
		GameObject& operator=(GameObject&& other)		= delete;

		void Update(float deltaTime);
		void Render() const;

		template <typename T, typename... Args>
		T* AddComponent(Args&&... args);

		template <typename T>
		void RemoveComponent();

		template <typename T>
		T* GetComponent() const;

		template <typename T>
		bool HasComponent() const;

	private:
		std::vector<std::unique_ptr<Component>> m_Components;
		std::unordered_map<std::type_index, Component*> m_ComponentMap;
	};
}
