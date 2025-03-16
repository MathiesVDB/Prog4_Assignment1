#pragma once
#include <vector>

#include "Singleton.h"

class Observer
{
public:
    virtual ~Observer() = default;
    virtual void OnNotify(const Entity& entity, Event event) = 0;
};

class Subject
{
public:
    void AddObserver(Observer* observer)
    {
        m_Observers.push_back(observer);
    }

    void RemoveObserver(Observer* observer)
    {
        m_Observers.erase(std::remove(m_Observers.begin(), m_Observers.end(), observer), m_Observers.end());
    }

    void Notify(int newLives)
    {
        for (Observer* observer : m_Observers)
        {
            observer->OnNotify(newLives);
        }
    }

private:
    std::vector<Observer*> m_Observers;
};