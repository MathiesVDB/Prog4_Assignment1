#include <SDL.h>

#if _DEBUG
// ReSharper disable once CppUnusedIncludeDirective
#if __has_include(<vld.h>)
#include <vld.h>
#endif
#endif

#include "FPSComponent.h"
#include "Minigin.h"
#include "SceneManager.h"
#include "ResourceManager.h"
#include "TextObject.h"
#include "Scene.h"
#include "TextureComponent.h"
#include "Transform.h"

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

    auto ParentGameObject = std::make_shared<dae::GameObject>();
    ParentGameObject->GetComponent<Transform>()->SetPosition(100, 100, 0);
    ParentGameObject->AddComponent<TextureComponent>("Logo.tga");
    scene.Add(ParentGameObject);

	auto GameCharacter1GameObject = std::make_shared<dae::GameObject>();
	GameCharacter1GameObject->AddComponent<TextureComponent>("enemy1.bmp");
    GameCharacter1GameObject->GetComponent<Transform>()->SetPosition(50, 50, 0);
    GameCharacter1GameObject->GetComponent<Transform>()->SetMovementPattern(Transform::MovementPattern::Circle);
    GameCharacter1GameObject->SetParent(ParentGameObject.get(), true);
	scene.Add(GameCharacter1GameObject);

    auto GameCharacter2GameObject = std::make_shared<dae::GameObject>();
    GameCharacter2GameObject->AddComponent<TextureComponent>("enemy2.bmp");
    GameCharacter2GameObject->GetComponent<Transform>()->SetPosition(50, 50, 0);
    GameCharacter2GameObject->GetComponent<Transform>()->SetMovementPattern(Transform::MovementPattern::Circle);
	GameCharacter2GameObject->GetComponent<Transform>()->SetSpeed(90.f);
    GameCharacter2GameObject->SetParent(GameCharacter1GameObject.get(), false);
    scene.Add(GameCharacter2GameObject);
}

int main(int, char*[]) {
	dae::Minigin engine("../Data/");
	engine.Run(load);
    return 0;
}