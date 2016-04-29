#ifndef BASEINPUTMANAGER_H
#define BASEINPUTMANAGER_H

#include "BaseGameState.h"
#include "../../Utlity/HeroCommand.h"
#include "../../Display/Menus/Menu.h"

//********************************* CONSTANTS *********************************


//********************************* INITIALIZATION *********************************

class BaseInputManager  {
public:
	
	BaseInputManager::BaseInputManager(){} 

	void BaseInputManager ::	init();	
/*/ Purpose: init members 
Side Effects:  init status, speedMode
Triggers: spriteInit, loadHero
/*/
	
//********************************* KEY CYCLE *********************************

	virtual void BaseInputManager::		pollKeyEvents();
	virtual void BaseInputManager::		keyDown(SDL_Keycode key);
	virtual void BaseInputManager::		keyUp(SDL_Keycode key);
	void BaseInputManager::		clearKeys();

//********************************* INPUT RESPONSES *********************************
	
	virtual void BaseInputManager::		checkToggles();
	virtual MoveCommand * BaseInputManager::	directionInput();
	virtual Command * BaseInputManager::		mouseInput();
	Command * BaseInputManager::		actionInput();
	void BaseInputManager::		menuInput(Menu *screen);

//********************************* MEMBER FUNCTIONS *********************************

	void BaseInputManager::		on(SDL_Keycode key);
	void BaseInputManager::		off(SDL_Keycode key);

	XZI BaseInputManager::		mousePos();


//************************************************** MEMBERS ***************************************************
protected:
	static const int D = 4;
	static const int KEYS = 256;
	static const int SKEYS = 20;

		SDL_Keycode dKey[D];
		SDL_Keycode dArrow[D];

		bool keyPressed[KEYS];		//keyboard state array
		bool specialKeyPressed[SKEYS];	//special key state array
		bool mouseR, mouseL;		
		int mX, mY;

		SDL_Event ev;
		MoveCommand movecmd;
};

#endif