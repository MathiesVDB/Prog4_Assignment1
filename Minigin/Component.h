#pragma once

class GameObject;

class Component
{
public:
	Component() = default;
    virtual ~Component() = default;
    Component(const Component& other) = delete;
    Component(Component&& other) = delete;
    Component& operator=(const Component& other) = delete;
    Component& operator=(Component&& other) = delete;

    virtual void Update(float deltaTime) = 0;
    virtual void Render() const = 0;

    void SetOwner(GameObject* owner) { m_OwnerPtr = owner; }
    GameObject* GetOwner() const { return m_OwnerPtr; }

private:
    GameObject* m_OwnerPtr{ nullptr };
};
