#pragma once
#include <vector>
#include <memory>
#include <algorithm>
#include "GameObject.h"
#include "TextObject.h"
#include "HealthComponent.h"
#include "Singleton.h"

enum class Event
{
    HealthChanged
};

class Observer : public dae::Singleton<Observer>
{
public:
    using CallbackFunction = void(*)();

    void AddEventListener(Event event, CallbackFunction callback)
	{
        m_EventListeners[event].push_back(callback);
    }

    void Notify(Event event)
	{
        auto iterator = m_EventListeners.find(event);
		if (iterator == m_EventListeners.end()) return;

        for (const auto& callbackFunction : iterator->second)
        {
            callbackFunction();
        }
    }

private:
    std::unordered_map<Event, std::vector<CallbackFunction>> m_EventListeners;
};

class HealthDisplay
{
public:
    explicit HealthDisplay(std::shared_ptr<dae::GameObject> displayObject)
        : m_DisplayObject(displayObject)
	{

        Observer::GetInstance().AddEventListener(Event::HealthChanged, &HealthDisplay::UpdateText);
    }

    static void UpdateText()
	{
        if (!instance) return;

        auto textComponent = instance->m_DisplayObject->GetComponent<dae::TextObject>();
        if (!textComponent) return;

        textComponent->SetText("Lives: " + std::to_string(instance->m_Lives));
    }

    void SetLives(int lives) { m_Lives = lives; instance = this; }

private:
    std::shared_ptr<dae::GameObject> m_DisplayObject;
    int m_Lives = 0;
    static HealthDisplay* instance;
};