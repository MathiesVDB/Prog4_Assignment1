#include "GameObject.h"

namespace dae
{
    void GameObject::Update(float deltaTime)
    {
        for (auto& component : m_Components)
        {
            component->Update(deltaTime);
        }
    }

    void GameObject::Render() const
    {
        for (const auto& component : m_Components)
        {
            component->Render();
        }
    }

    template <typename T, typename... Args>
    T* GameObject::AddComponent(Args&&... args)
    {
        static_assert(std::is_base_of_v<Component, T>, "T must be derived from Component");

        auto component = std::make_unique<T>(std::forward<Args>(args)...);
        component->SetOwner(this);
        T* componentPtr = component.get();
        m_Components.push_back(std::move(component));
        m_ComponentMap[std::type_index(typeid(T))] = componentPtr;
        return componentPtr;
    }

    template <typename T>
    void GameObject::RemoveComponent()
    {
        static_assert(std::is_base_of_v<Component, T>, "T must be derived from Component");

        auto it = std::remove_if(m_Components.begin(), m_Components.end(),
            [](const std::unique_ptr<Component>& component)
            {
                return dynamic_cast<T*>(component.get()) != nullptr;
            });

        if (it != m_Components.end())
        {
            m_ComponentMap.erase(std::type_index(typeid(T)));
            m_Components.erase(it, m_Components.end());
        }
    }

    template <typename T>
    T* GameObject::GetComponent() const
    {
        static_assert(std::is_base_of_v<Component, T>, "T must be derived from Component");

        auto it = m_ComponentMap.find(std::type_index(typeid(T)));
        if (it != m_ComponentMap.end())
        {
            return static_cast<T*>(it->second);
        }
        return nullptr;
    }

    template <typename T>
    bool GameObject::HasComponent() const
    {
        static_assert(std::is_base_of_v<Component, T>, "T must be derived from Component");

        return m_ComponentMap.find(std::type_index(typeid(T))) != m_ComponentMap.end();
    }
}