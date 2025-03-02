#pragma once

//-----------------------------------------------------
// Include Files
//-----------------------------------------------------
#include "Component.h"
#include "imgui.h"
#include "imgui_plot.h"
#include <vector>

//-----------------------------------------------------
// PlotComponent Class
//-----------------------------------------------------
class PlotComponent final : public Component
{
public:
    PlotComponent(); // Constructor

    // Copy/move constructors and assignment operators
    PlotComponent(const PlotComponent& other) = default;
    PlotComponent(PlotComponent&& other) noexcept = default;
    PlotComponent& operator=(const PlotComponent& other) = default;
    PlotComponent& operator=(PlotComponent&& other) noexcept = default;

    //-------------------------------------------------
    // Member functions
    //-------------------------------------------------
    void Update(float deltaTime) override;
    void Render() const override;

private:
    //-------------------------------------------------
    // Datamembers
    //-------------------------------------------------

};
