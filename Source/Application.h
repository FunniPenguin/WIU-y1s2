
#ifndef APPLICATION_H
#define APPLICATION_H

#include "timer.h"

class Application
{
public:
	Application();
	~Application();
	void Init();
	void Run();
	void Exit();
	static bool IsKeyPressed(unsigned short key);

private:

	//Declare a window object
	StopWatch m_timer;

	//To utilise the mouse in game, set to true
	bool enablePointer = true;
	//To display the mouse pointer in game, set to true
	bool showPointer = true;

	//void UpdateKeyStates();
};

#endif