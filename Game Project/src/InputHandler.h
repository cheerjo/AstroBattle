#include <SDL.h>
#include <vector>
#include "Vector2D.h"
#pragma once
enum mouse_buttons
{
	LEFT = 0,
	MIDDLE = 1,
	RIGHT = 2
};
class InputHandler
{
public:
	static InputHandler* Instance()
	{
		if (s_pInstance == 0)
		{
			s_pInstance = new InputHandler();
		}
		return s_pInstance;
	}
	void update();
	void clean();
	void initialiseJoysticks();
	bool joysticksInitialised() { return m_bJoysticksInitialised; }
	bool getButtonState(int joy, int buttonNumber)
	{
		return m_buttonStates[joy][buttonNumber];
	}
	bool getMouseButtonState(int buttonNumber)
	{
		return m_mouseButtonStates[buttonNumber];
	}
	Vector2D* getMousePosition()
	{
		return m_mousePosition;
	}
	int xvalue(int joy, int stick);
	int yvalue(int joy, int stick);
	
	
private:
	float m_mouseX = 0;
	float m_mouseY = 0;
	Vector2D* m_mousePosition = NULL;
	std::vector<std::pair<Vector2D*, Vector2D*>> m_joystickValues;
	std::vector<std::vector<bool>> m_buttonStates;
	std::vector<bool> m_mouseButtonStates;
	~InputHandler() {}
	InputHandler();

	// handle keyboard events
	//void onKeyDown();
	//void onKeyUp();
	// handle mouse events
	void onMouseMove(SDL_Event& event);
	void onMouseButtonDown(SDL_Event& event);
	void onMouseButtonUp(SDL_Event& event);
	// handle joysticks events
	//void onJoystickAxisMove(SDL_Event& event);
	//void onJoystickButtonDown(SDL_Event& event);
	//void onJoystickButtonUp(SDL_Event& event);
	std::vector<SDL_Joystick*> m_joysticks;
	bool m_bJoysticksInitialised;

	static InputHandler* s_pInstance;
	const int m_joystickDeadZone = 10000;
};
typedef InputHandler TheInputHandler;
