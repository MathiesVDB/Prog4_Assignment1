#include "GameObject.h"

namespace dae
{
	GameObject::GameObject()
	{
        AddComponent<Transform>();
	}

    GameObject::~GameObject() = default;

	void GameObject::Update(float deltaTime)
    {
        for (const auto& [type, component] : m_Components)
        {
            component->Update(deltaTime);
        }
    }

    void GameObject::Render() const
    {
        for (const auto& [type, component] : m_Components)
        {
            component->Render();
        }
    }
}