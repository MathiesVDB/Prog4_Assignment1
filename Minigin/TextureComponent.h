#pragma once
#include "Component.h"
#include <string>
#include <SDL.h>
#include "GameObject.h"

class TextureComponent final : public Component
{
public:
    TextureComponent(GameObject* owner, std::string  filename);
    ~TextureComponent() override;
    TextureComponent(const TextureComponent&) = delete;
    TextureComponent(TextureComponent&&) = delete;
    TextureComponent& operator= (const TextureComponent&) = delete;
    TextureComponent& operator= (const TextureComponent&&) = delete;

    void Update(float deltaTime) override { (void)deltaTime; }
    void Render() const override;

    void SetTexture(const std::string& filename);

private:
    SDL_Texture* m_Texture{ nullptr };
    std::string m_Filename;

	GameObject* m_Owner;
};