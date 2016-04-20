#ifndef BASEINPUTMANAGER_H
#define BASEINPUTMANAGER_H

#include "BaseGameState.h"
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
	void BaseInputManager::		menuInput(Menu *screen);

//************************************************** MEMBERS ***************************************************
	

		bool keyPressed[256];		//keyboard state array
		bool specialKeyPressed[20];	//special key state array
		
		SDL_Event ev;

//********************************* MEMBER FUNCTIONS *********************************

	void BaseInputManager::		on(SDL_Keycode key);
	void BaseInputManager::		off(SDL_Keycode key);

};

#endif