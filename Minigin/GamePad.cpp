#include "Gamepad.h"
#include <Windows.h>
#include <Xinput.h>
#include <memory>

#pragma comment(lib, "xinput.lib")

class GamePad::GamepadImpl
{
public:
	explicit GamepadImpl(int controllerIndex)
		: m_ControllerIndex(controllerIndex)
	{
		ZeroMemory(&m_CurrentState, sizeof(XINPUT_STATE));
		ZeroMemory(&m_PreviousState, sizeof(XINPUT_STATE));
	}

	void Update()
	{
		// Store previous state
		m_PreviousState = m_CurrentState;

		// Poll controller
		ZeroMemory(&m_CurrentState, sizeof(XINPUT_STATE));
		XInputGetState(m_ControllerIndex, &m_CurrentState);

		// Detect button changes
		auto buttonChanges = m_CurrentState.Gamepad.wButtons ^ m_PreviousState.Gamepad.wButtons;
		m_ButtonsPressedThisFrame = buttonChanges & m_CurrentState.Gamepad.wButtons;
		m_ButtonsReleasedThisFrame = buttonChanges & (~m_CurrentState.Gamepad.wButtons);
	}

	bool IsButtonDown(unsigned int button) const { return (m_ButtonsPressedThisFrame & button) != 0; }
	bool IsButtonUp(unsigned int button) const { return (m_ButtonsReleasedThisFrame & button) != 0; }
	bool IsButtonPressed(unsigned int button) const { return (m_CurrentState.Gamepad.wButtons & button) != 0; }

private:
	int m_ControllerIndex{};
	XINPUT_STATE m_CurrentState{};
	XINPUT_STATE m_PreviousState{};
	unsigned int m_ButtonsPressedThisFrame{};
	unsigned int m_ButtonsReleasedThisFrame{};
};

GamePad::GamePad(int controllerIndex)
	: m_pImpl(std::make_unique<GamepadImpl>(controllerIndex))
{
}

GamePad::~GamePad() = default;
void GamePad::Update() { m_pImpl->Update(); }
bool GamePad::IsButtonDown(unsigned int button) const { return m_pImpl->IsButtonDown(button); }
bool GamePad::IsButtonUp(unsigned int button) const { return m_pImpl->IsButtonUp(button); }
bool GamePad::IsButtonPressed(unsigned int button) const { return m_pImpl->IsButtonPressed(button); }