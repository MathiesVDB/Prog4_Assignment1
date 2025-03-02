#include <stdexcept>
#include "Renderer.h"

#include <chrono>
#include <iostream>

#include "imgui.h"
#include "SceneManager.h"
#include "Texture2D.h"
#include "backends/imgui_impl_opengl3.h"
#include "backends/imgui_impl_sdl2.h"
#include "imgui_plot.h"

int GetOpenGLDriverIndex()
{
	auto openglIndex = -1;
	const auto driverCount = SDL_GetNumRenderDrivers();
	for (auto i = 0; i < driverCount; i++)
	{
		SDL_RendererInfo info;
		if (!SDL_GetRenderDriverInfo(i, &info))
			if (!strcmp(info.name, "opengl"))
				openglIndex = i;
	}
	return openglIndex;
}

void dae::Renderer::Init(SDL_Window* window)
{
	m_window = window;
	m_renderer = SDL_CreateRenderer(window, GetOpenGLDriverIndex(), SDL_RENDERER_ACCELERATED);
	if (m_renderer == nullptr)
	{
		throw std::runtime_error(std::string("SDL_CreateRenderer Error: ") + SDL_GetError());
	}

	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGui_ImplSDL2_InitForOpenGL(window, SDL_GL_GetCurrentContext());
	ImGui_ImplOpenGL3_Init();
}

void dae::Renderer::Render() const
{
	const auto& color = GetBackgroundColor();
	SDL_SetRenderDrawColor(m_renderer, color.r, color.g, color.b, color.a);
	SDL_RenderClear(m_renderer);

	SceneManager::GetInstance().Render();

	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplSDL2_NewFrame();
	ImGui::NewFrame();

	static std::vector<float> durations1;
	static std::vector<float> stepsizes1;

	static std::vector<float> durations2;
	static std::vector<float> stepsizes2;

	static std::vector<float> durations3;
	static std::vector<float> stepsizes3;

	if (ImGui::Button("Trash the Cache"))
	{
		GetData(1, durations1, stepsizes1);
	}

	if (!durations1.empty())
	{
		ImGui::PlotConfig conf;
		conf.values.xs = stepsizes1.data();
		conf.values.ys = durations1.data();
		conf.values.count = static_cast<int>(durations1.size());
		conf.scale.min = 0;
		conf.scale.max = *std::max_element(durations1.begin(), durations1.end());
		conf.tooltip.show = true;
		conf.grid_x.show = true;
		conf.grid_y.show = true;
		conf.frame_size = ImVec2(400, 200);
		ImGui::Plot("Cache Trash Durations", conf);
	}

	ImGui::Begin("Exercise 3", nullptr, ImGuiWindowFlags_AlwaysAutoResize);

	if (ImGui::Button("Trash the Cache with GameObject3D"))
	{
		GetData(2, durations2, stepsizes2);  
	}

	if (!durations2.empty())
	{
		ImGui::PlotConfig conf2;
		conf2.values.xs = stepsizes2.data();
		conf2.values.ys = durations2.data();
		conf2.values.count = static_cast<int>(durations2.size());
		conf2.scale.min = 0;
		conf2.scale.max = *std::max_element(durations2.begin(), durations2.end());
		conf2.tooltip.show = true;
		conf2.grid_x.show = true;
		conf2.grid_y.show = true;
		conf2.frame_size = ImVec2(400, 200);
		ImGui::Plot("Cache Trash Durations GameObject3D", conf2);
	}

	if (ImGui::Button("Trash the Cache with GameObject3DAlt"))
	{
		GetData(3, durations3, stepsizes3);  
	}

	if (!durations3.empty())
	{
		ImGui::PlotConfig conf3;
		conf3.values.xs = stepsizes3.data();
		conf3.values.ys = durations3.data();
		conf3.values.count = static_cast<int>(durations3.size());
		conf3.scale.min = 0;
		conf3.scale.max = *std::max_element(durations3.begin(), durations3.end());
		conf3.tooltip.show = true;
		conf3.grid_x.show = true;
		conf3.grid_y.show = true;
		conf3.frame_size = ImVec2(400, 200);
		ImGui::Plot("Cache Trash Durations GameObject3DAlt", conf3);
	}

	if (!durations2.empty() && !durations3.empty())
	{
		const float* ys_list[] = { durations2.data(), durations3.data() };
		ImGui::PlotConfig confCombined;
		confCombined.values.xs = stepsizes2.data(); // Assuming stepsizes2 and stepsizes3 are the same
		confCombined.values.ys_list = ys_list;
		confCombined.values.ys_count = 2;
		confCombined.values.count = static_cast<int>(durations2.size());
		confCombined.scale.min = 0;
		confCombined.scale.max = std::max(*std::max_element(durations2.begin(), durations2.end()), *std::max_element(durations3.begin(), durations3.end()));
		confCombined.tooltip.show = true;
		confCombined.grid_x.show = true;
		confCombined.grid_y.show = true;
		confCombined.frame_size = ImVec2(400, 200);
		ImGui::Plot("Combined Cache Trash Durations", confCombined);
	}

	ImGui::End();

	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

	SDL_RenderPresent(m_renderer);
}

void dae::Renderer::Destroy()
{
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplSDL2_Shutdown();
	ImGui::DestroyContext();

	if (m_renderer != nullptr)
	{
		SDL_DestroyRenderer(m_renderer);
		m_renderer = nullptr;
	}
}

void dae::Renderer::RenderTexture(const Texture2D& texture, const float x, const float y) const
{
	SDL_Rect dst{};
	dst.x = static_cast<int>(x);
	dst.y = static_cast<int>(y);
	SDL_QueryTexture(texture.GetSDLTexture(), nullptr, nullptr, &dst.w, &dst.h);
	SDL_RenderCopy(GetSDLRenderer(), texture.GetSDLTexture(), nullptr, &dst);
}

void dae::Renderer::RenderTexture(const Texture2D& texture, const float x, const float y, const float width, const float height) const
{
	SDL_Rect dst{};
	dst.x = static_cast<int>(x);
	dst.y = static_cast<int>(y);
	dst.w = static_cast<int>(width);
	dst.h = static_cast<int>(height);
	SDL_RenderCopy(GetSDLRenderer(), texture.GetSDLTexture(), nullptr, &dst);
}

SDL_Renderer* dae::Renderer::GetSDLRenderer() const { return m_renderer; }

void dae::Renderer::GetData(int ex, std::vector<float>& durations, std::vector<float>& stepsizes) const
{
	int numSamples = 5000000;
	durations.clear();
	stepsizes.clear();

	if (ex == 1)
	{
		// Exercise 1:
		std::vector<int> vec(numSamples, 0);

		for (int stepsize = 1; stepsize <= 1024; stepsize *= 2)
		{
			auto start = std::chrono::high_resolution_clock::now();
			for (int i = 0; i < numSamples; i += stepsize)
			{
				vec[i] *= 2;
			}
			auto end = std::chrono::high_resolution_clock::now();
			auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
			durations.push_back(static_cast<float>(duration.count()));
			stepsizes.push_back(static_cast<float>(stepsize));
		}
	}
	else if (ex == 2)
	{
		// Exercise 2:
		std::vector<GameObject3D> vec(numSamples);

		for (int stepsize = 1; stepsize <= 1024; stepsize *= 2)
		{
			auto start = std::chrono::high_resolution_clock::now();
			for (int i = 0; i < numSamples; i += stepsize)
			{
				vec[i].ID *= 2;
			}
			auto end = std::chrono::high_resolution_clock::now();
			auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
			durations.push_back(static_cast<float>(duration.count()));
			stepsizes.push_back(static_cast<float>(stepsize));
		}
	}
	else
	{
		// Exercise 3:
		std::vector<GameObject3DAlt> vec(numSamples);

		for (int stepsize = 1; stepsize <= 1024; stepsize *= 2)
		{
			auto start = std::chrono::high_resolution_clock::now();
			for (int i = 0; i < numSamples; i += stepsize)
			{
				vec[i].ID *= 2;
			}
			auto end = std::chrono::high_resolution_clock::now();
			auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
			durations.push_back(static_cast<float>(duration.count()));
			stepsizes.push_back(static_cast<float>(stepsize));
		}
	}
}

