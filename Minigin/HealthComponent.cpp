//---------------------------
// Include Files
//---------------------------
#include "HealthComponent.h"

//---------------------------
// Constructor & Destructor
//---------------------------
HealthComponent::HealthComponent(int maxLives)
	: m_MaxLives{maxLives}
{
	m_Lives = m_MaxLives;
}

//---------------------------
// Member functions
//---------------------------

int HealthComponent::GetLives() const
{
	return m_Lives;
}

void HealthComponent::SetMaxLives(int newMaxLives)
{
	m_MaxLives = newMaxLives;
}

void HealthComponent::TakeDamage(int takenDamage)
{
	m_Lives -= takenDamage;
	Notify(m_Lives);
}

void HealthComponent::SetLivesToMax()
{
	m_Lives = m_MaxLives;
	Notify(m_Lives);
}