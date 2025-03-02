//---------------------------
// Include Files
//---------------------------
#include "PlotComponent.h"
#include "imgui.h"
#include "imgui_plot.h"
#include <cmath>
#include <iostream>

#include "backends/imgui_impl_opengl3.h"
#include "backends/imgui_impl_sdl2.h"

//---------------------------
// Constructor & Destructor
//---------------------------
PlotComponent::PlotComponent()
{
}

//---------------------------
// Member functions
//---------------------------
void PlotComponent::Update(float )
{
   
}

void PlotComponent::Render() const
{
    /*ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplSDL2_NewFrame();
    ImGui::NewFrame();
    
    ImGui::Begin("First Window");
    if (ImGui::Button("Exercise"))
    {
		std::cout << "Button pressed" << std::endl;
    }
    ImGui::End();
    
    ImGui::Begin("Second Window");
    if (ImGui::Button("Exercise"))
    {
        std::cout << "Button 2 pressed" << std::endl;
    }
    ImGui::End();
    
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());*/
}
