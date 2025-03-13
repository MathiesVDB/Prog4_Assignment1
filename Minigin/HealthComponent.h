#pragma once

//-----------------------------------------------------
// Include Files
//-----------------------------------------------------
#include "Component.h"

//-----------------------------------------------------
// HealthComponent Class									 
//-----------------------------------------------------
class HealthComponent final : public Component
{
public:
	HealthComponent(); // Constructor
	~HealthComponent(); // Destructor

	// -------------------------
	// Copy/move constructors and assignment operators
	// -------------------------    
	HealthComponent(const HealthComponent& other)					= default;
	HealthComponent(HealthComponent&& other) noexcept				= default;
	HealthComponent& operator=(const HealthComponent& other)		= default;
	HealthComponent& operator=(HealthComponent&& other) noexcept	= default;

	//-------------------------------------------------
	// Member functions						
	//-------------------------------------------------


private:
	//-------------------------------------------------
	// Private member functions								
	//-------------------------------------------------


	//-------------------------------------------------
	// Datamembers								
	//-------------------------------------------------
};
