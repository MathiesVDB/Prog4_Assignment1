#include <SDL.h>

#if _DEBUG
// ReSharper disable once CppUnusedIncludeDirective
#if __has_include(<vld.h>)
#include <vld.h>
#endif
#endif

#include <SDL_syswm.h>
#include <XInput.h>
#include <steam_api.h>

#include "Achievement.h"
#include "FPSComponent.h"
#include "HealthComponent.h"
#include "HealthDisplayer.h"
#include "Minigin.h"
#include "PlotComponent.h"
#include "SceneManager.h"
#include "ResourceManager.h"
#include "TextObject.h"
#include "Scene.h"
#include "TextureComponent.h"
#include "Transform.h"
#include "InputManager.h"
#include "Observer.h"

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

	font = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 15);
	auto How2PlayGameObject = std::make_shared<dae::GameObject>();
	How2PlayGameObject->AddComponent<dae::TextObject>("Use WASD to move the second player, C to inflict damage, Z and X to pick up pellets", font);
	How2PlayGameObject->GetComponent<Transform>()->SetPosition(10, 70, 0);
	scene.Add(How2PlayGameObject);

    auto FPSGameObject = std::make_shared<dae::GameObject>();
    FPSGameObject->AddComponent<FPSComponent>();
    scene.Add(FPSGameObject);

	auto Player1 = std::make_shared<dae::GameObject>();
	Player1->AddComponent<TextureComponent>("enemy1.bmp");
	Player1->GetComponent<Transform>()->SetPosition(180, 90, 0);
	Player1->AddComponent<HealthComponent>(3);
	scene.Add(Player1);

	auto lifeDisplay1GameObject = std::make_shared<dae::GameObject>();
	lifeDisplay1GameObject->AddComponent<dae::TextObject>("Lives: " + std::to_string(Player1->GetComponent<HealthComponent>()->GetLives()), font);
	lifeDisplay1GameObject->GetComponent<Transform>()->SetPosition(10, 150, 0);
	scene.Add(lifeDisplay1GameObject);

	auto healthDisplay = std::make_shared<HealthDisplay>(lifeDisplay1GameObject.get(), Player1.get());
	Player1->GetComponent<HealthComponent>()->AddObserver(healthDisplay);

	//auto scoreDisplay = std::make_shared<ScoreDisplay>();
	//scoreDisplay->SetScore(Player1->GetComponent<HealthComponent>()->GetLives());
	
	auto Player2 = std::make_shared<dae::GameObject>();
	Player2->AddComponent<TextureComponent>("enemy2.bmp");
	Player2->GetComponent<Transform>()->SetPosition(80, 90, 0);
	scene.Add(Player2);

	auto& inputManager = InputManager::GetInstance();

	inputManager.AddCommand(SDL_SCANCODE_W, KeyState::Pressed, std::make_shared<MoveCommand>(Player1.get(), MoveCommand::Direction::Up));
	inputManager.AddCommand(SDL_SCANCODE_A, KeyState::Pressed, std::make_shared<MoveCommand>(Player1.get(), MoveCommand::Direction::Left));
	inputManager.AddCommand(SDL_SCANCODE_S, KeyState::Pressed, std::make_shared<MoveCommand>(Player1.get(), MoveCommand::Direction::Down));
	inputManager.AddCommand(SDL_SCANCODE_D, KeyState::Pressed, std::make_shared<MoveCommand>(Player1.get(), MoveCommand::Direction::Right));

	inputManager.AddCommand(SDL_SCANCODE_C, KeyState::Pressed, std::make_shared<DamageCommand>(Player1.get()));
	//inputManager.AddCommand(SDL_SCANCODE_C, KeyState::Pressed, std::make_shared<PickupPelletCommand>(Player1.get()));
	//inputManager.AddCommand(SDL_SCANCODE_C, KeyState::Pressed, std::make_shared<PickupPelletCommand>(Player1.get()));
	
	//inputManager.AddControllerCommand(XINPUT_GAMEPAD_DPAD_UP   , KeyState::Pressed, std::make_shared<MoveCommand>(enemy1.get(), MoveCommand::Direction::Up));
	//inputManager.AddControllerCommand(XINPUT_GAMEPAD_DPAD_LEFT, KeyState::Pressed , std::make_shared<MoveCommand>(enemy1.get(), MoveCommand::Direction::Left));
	//inputManager.AddControllerCommand(XINPUT_GAMEPAD_DPAD_DOWN, KeyState::Pressed , std::make_shared<MoveCommand>(enemy1.get(), MoveCommand::Direction::Down));
	//inputManager.AddControllerCommand(XINPUT_GAMEPAD_DPAD_RIGHT, KeyState::Pressed, std::make_shared<MoveCommand>(enemy1.get(), MoveCommand::Direction::Right));
}

int main(int, char*[]) {

	if (!SteamAPI_Init())
	{
		std::cerr << "Fatal Error - Steam must be running to play this game (SteamAPI_Init() failed)." << std::endl;
		return 1;
	}
	else
	{
		std::cout << "Successfully initialized steam." << std::endl;

		CSteamAchievements::GetInstance();
	}

	dae::Minigin engine("../Data/");
	engine.Run(load);

	SteamAPI_Shutdown();

    return 0;
}