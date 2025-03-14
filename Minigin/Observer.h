#pragma once
#include "Singleton.h"

class Observer final : public dae::Singleton<Observer>
{
public:
	Observer();
	~Observer();

	// -------------------------
	// Copy/move constructors and assignment operators
	// -------------------------    
	Observer(const Observer& other)					= default;
	Observer(Observer&& other) noexcept				= default;
	Observer& operator=(const Observer& other)		= default;
	Observer& operator=(Observer&& other) noexcept	= default;

	//-------------------------------------------------
	// Member functions						
	//-------------------------------------------------
	

private:

};