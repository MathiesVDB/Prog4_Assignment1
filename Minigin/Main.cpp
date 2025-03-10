#include <SDL.h>

#if _DEBUG
// ReSharper disable once CppUnusedIncludeDirective
#if __has_include(<vld.h>)
#include <vld.h>
#endif
#endif

#include <SDL_syswm.h>
#include <XInput.h>

#include "FPSComponent.h"
#include "Minigin.h"
#include "PlotComponent.h"
#include "SceneManager.h"
#include "ResourceManager.h"
#include "TextObject.h"
#include "Scene.h"
#include "TextureComponent.h"
#include "Transform.h"
#include "InputManager.h"

using namespace dae;

void load()
{
    auto& scene = dae::SceneManager::GetInstance().CreateScene("Demo");

    auto backgroundGameObject = std::make_shared<dae::GameObject>();
    backgroundGameObject->AddComponent<TextureComponent>("background.tga");
    scene.Add(backgroundGameObject);

    auto logoGameObject = std::make_shared<dae::GameObject>();
    logoGameObject->AddComponent<TextureComponent>("logo.tga");
    logoGameObject->GetComponent<Transform>()->SetPosition(216, 180, 0);
    scene.Add(logoGameObject);

    auto font = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);
    auto textGameObject = std::make_shared<dae::GameObject>();
    textGameObject->AddComponent<dae::TextObject>("Programming 4 Assignment", font);
    textGameObject->GetComponent<Transform>()->SetPosition(80, 20, 0);
    scene.Add(textGameObject);

    auto FPSGameObject = std::make_shared<dae::GameObject>();
    FPSGameObject->AddComponent<FPSComponent>();
    scene.Add(FPSGameObject);

	auto enemy1 = std::make_shared<dae::GameObject>();
	enemy1->AddComponent<TextureComponent>("enemy1.bmp");
	enemy1->GetComponent<Transform>()->SetPosition(180, 90, 0);
	scene.Add(enemy1);
	
	auto enemy2 = std::make_shared<dae::GameObject>();
	enemy2->AddComponent<TextureComponent>("enemy2.bmp");
	enemy2->GetComponent<Transform>()->SetPosition(80, 90, 0);
	scene.Add(enemy2);

	auto& inputManager = InputManager::GetInstance();

	inputManager.AddCommand(SDL_SCANCODE_W, KeyState::Pressed, std::make_shared<MoveUpCommand>(enemy1.get()));
	inputManager.AddCommand(SDL_SCANCODE_A, KeyState::Pressed, std::make_shared<MoveLeftCommand>(enemy1.get()));
	inputManager.AddCommand(SDL_SCANCODE_S, KeyState::Pressed, std::make_shared<MoveDownCommand>(enemy1.get()));
	inputManager.AddCommand(SDL_SCANCODE_D, KeyState::Pressed, std::make_shared<MoveRightCommand>(enemy1.get()));
	
	inputManager.AddControllerCommand(XINPUT_GAMEPAD_DPAD_UP   , KeyState::Pressed, std::make_shared<MoveUpCommand>(enemy1.get()));
	inputManager.AddControllerCommand(XINPUT_GAMEPAD_DPAD_LEFT, KeyState::Pressed , std::make_shared<MoveLeftCommand>(enemy1.get()));
	inputManager.AddControllerCommand(XINPUT_GAMEPAD_DPAD_DOWN, KeyState::Pressed , std::make_shared<MoveDownCommand>(enemy1.get()));
	inputManager.AddControllerCommand(XINPUT_GAMEPAD_DPAD_RIGHT, KeyState::Pressed, std::make_shared<MoveRightCommand>(enemy1.get()));
}

int main(int, char*[]) {
	dae::Minigin engine("../Data/");
	engine.Run(load);
    return 0;
}