#pragma once
#include "SDLGameObject.h"
class MenuButton : public SDLGameObject
{
public:

	MenuButton(const LoaderParams* pParams, void (*callback)());
	virtual void draw();
	virtual void update();
	virtual void clean();
	void setCallback(void(*callback)()){ m_callback = callback; }
	int getCallbackID(){ return m_callbackID; }

private:
	enum button_state
	{
		MOUSE_OUT = 0,
		MOUSE_OVER = 1,
		CLICKED = 2
	};

	void(*m_callback)();
	bool m_bReleased;
	int m_callbackID;
};