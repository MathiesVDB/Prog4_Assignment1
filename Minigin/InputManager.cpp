#include "InputManager.h"
#include "Gamepad.h"
#include <SDL.h>
#include <unordered_map>
#include <vector>
#include <memory>

class InputManager::InputManagerImpl
{
public:
	InputManagerImpl()
		: m_Gamepad(0) // Controller 0
	{
		memset(m_PreviousKeyboardState, 0, SDL_NUM_SCANCODES);
	}

	bool ProcessInput()
	{
		m_Gamepad.Update();

		const Uint8* keyboardState = SDL_GetKeyboardState(nullptr);

		for (const auto& [key, commands] : m_KeyboardCommands)
		{
			for (const auto& [keyState, command] : commands)
			{
				bool execute = false;
				switch (keyState)
				{
				case KeyState::Down:
					execute = keyboardState[key] && !m_PreviousKeyboardState[key];
					break;
				case KeyState::Up:
					execute = !keyboardState[key] && m_PreviousKeyboardState[key];
					break;
				case KeyState::Pressed:
					execute = keyboardState[key];
					break;
				}
				if (execute) command->Execute();
			}
		}

		for (const auto& [button, commands] : m_ControllerCommands)
		{
			for (const auto& [keyState, command] : commands)
			{
				bool execute = false;
				switch (keyState)
				{
				case KeyState::Down:
					execute = m_Gamepad.IsButtonDown(button);
					break;
				case KeyState::Up:
					execute = m_Gamepad.IsButtonUp(button);
					break;
				case KeyState::Pressed:
					execute = m_Gamepad.IsButtonPressed(button);
					break;
				}
				if (execute) command->Execute();
			}
		}

		memcpy(m_PreviousKeyboardState, keyboardState, SDL_NUM_SCANCODES);
		return true;
	}

	void AddCommand(unsigned int key, KeyState state, Command* command)
	{
		m_KeyboardCommands[key].emplace_back(state, command);
	}

	void AddControllerCommand(unsigned int button, KeyState state, Command* command)
	{
		m_ControllerCommands[button].emplace_back(state, command);
	}

private:
	std::unordered_map<unsigned int, std::vector<std::pair<KeyState, Command*>>> m_KeyboardCommands;
	std::unordered_map<unsigned int, std::vector<std::pair<KeyState, Command*>>> m_ControllerCommands;
	Uint8 m_PreviousKeyboardState[SDL_NUM_SCANCODES]{};
	GamePad m_Gamepad;
};

InputManager::InputManager()
	: m_pImpl(std::make_unique<InputManagerImpl>())
{
}

InputManager::~InputManager() = default;

bool InputManager::ProcessInput() { return m_pImpl->ProcessInput(); }
void InputManager::AddCommand(unsigned int key, KeyState state, Command* command) { m_pImpl->AddCommand(key, state, command); }
void InputManager::AddControllerCommand(unsigned int button, KeyState state, Command* command) { m_pImpl->AddControllerCommand(button, state, command); }
