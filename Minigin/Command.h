#pragma once
#include "Component.h"
#include "Transform.h"
#include "GameObject.h"

class Command
{
public:
	virtual ~Command() = default;
	virtual void Execute() = 0;
};

//------------------------------------------------
// Current Commands
//------------------------------------------------

class MoveLeftCommand final : public Command
{
public:
	explicit MoveLeftCommand(dae::GameObject* owner) : m_Owner(owner) {}
	void Execute() override
	{
		if (auto transform = m_Owner->GetComponent<dae::Transform>())
		{
			auto pos = transform->GetPosition();
			transform->SetPosition(pos.x - 5.f, pos.y, pos.z);
		}
	}

private:
	dae::GameObject* m_Owner;
};

class MoveRightCommand final : public Command
{
public:
	explicit MoveRightCommand(dae::GameObject* owner) : m_Owner(owner) {}
	void Execute() override
	{
		if (auto transform = m_Owner->GetComponent<dae::Transform>())
		{
			auto pos = transform->GetPosition();
			transform->SetPosition(pos.x + 5.f, pos.y, pos.z);
		}
	}

private:
	dae::GameObject* m_Owner;
};

class MoveUpCommand final : public Command
{
public:
	explicit MoveUpCommand(dae::GameObject* owner) : m_Owner(owner) {}
	void Execute() override
	{
		if (auto transform = m_Owner->GetComponent<dae::Transform>())
		{
			auto pos = transform->GetPosition();
			transform->SetPosition(pos.x, pos.y - 5.f, pos.z);
		}
	}

private:
	dae::GameObject* m_Owner;
};

class MoveDownCommand final : public Command
{
public:
	explicit MoveDownCommand(dae::GameObject* owner) : m_Owner(owner) {}
	void Execute() override
	{
		if (auto transform = m_Owner->GetComponent<dae::Transform>())
		{
			auto pos = transform->GetPosition();
			transform->SetPosition(pos.x, pos.y + 5.f, pos.z);
		}
	}

private:
	dae::GameObject* m_Owner;
};