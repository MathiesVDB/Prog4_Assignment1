#include "TextureComponent.h"
#include "Renderer.h"
#include "ResourceManager.h"
#include "TransformComponent.h"
#include "Texture2D.h"

TextureComponent::TextureComponent(GameObject* owner, std::string filename)
    : m_Filename(std::move(filename))
{
	m_Owner = owner;

    SetOwner(m_Owner); // Set the owner

    if (m_Owner && !m_Owner->GetComponent<TransformComponent>())
    {
        auto transform = m_Owner->AddComponent<TransformComponent>();
        transform->SetPosition(glm::vec3(0.0f, 0.0f, 0.0f)); // Standard position
    }
}

TextureComponent::~TextureComponent()
{
    if (m_Texture)
    {
        SDL_DestroyTexture(m_Texture);
        m_Texture = nullptr;
    }
}

void TextureComponent::Render() const
{
    if (!m_Texture) return;

    SDL_Rect dst{};

    if (auto owner = GetOwner())
    {
        if (auto transform = m_Owner->GetComponent<TransformComponent>())
        {
            const auto& pos = transform->GetPosition();
            dst.x = static_cast<int>(pos.x);
            dst.y = static_cast<int>(pos.y);
        }
    }

    SDL_QueryTexture(m_Texture, nullptr, nullptr, &dst.w, &dst.h);
    SDL_RenderCopy(dae::Renderer::GetInstance().GetSDLRenderer(), m_Texture, nullptr, &dst);
}

void TextureComponent::SetTexture(const std::string& filename)
{
    if (m_Filename == filename && m_Texture) return; // Avoid redundant loading

    m_Filename = filename;
    auto texture = dae::ResourceManager::GetInstance().LoadTexture(filename);

    if (texture)
    {
        if (m_Texture) SDL_DestroyTexture(m_Texture); // Clean up previous texture
        m_Texture = texture->GetSDLTexture();
    }
}
