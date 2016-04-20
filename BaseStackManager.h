#ifndef BASESTACKMANAGER_H
#define BASESTACKMANAGER_H

#include "BaseInputManager.h"


//********************************* CONSTANTS *********************************

//********************************* INITIALIZATION *********************************

class BaseStackManager {
public:
	BaseStackManager::BaseStackManager();
	// Constructor
	void BaseStackManager::	initMenus();	
	void BaseStackManager::	loadDefaults();


	// screen setup
	
	void BaseStackManager::setRootMenu();
	void BaseStackManager::	updateMenu();
	void BaseStackManager::	update(BaseInputManager &input);


	void BaseStackManager::	pushMenu(Menu * s);
	void BaseStackManager::	popMenu();


	
	void BaseStackManager::	rapidUpdate();
	
//********************************* DRAW *********************************
	void BaseStackManager::	draw();
	void BaseStackManager::	drawHUD();
	void BaseStackManager::	drawMenus();
	void BaseStackManager::	drawText();
	
	void BaseStackManager::	drawCursor();
	void BaseStackManager::	drawIcons();
	void BaseStackManager::	drawBackground();



	void BaseStackManager::	setUp2DView(int width, int height);
	void BaseStackManager::	disable2DView();
	/*/ Purpose: 
Side Effects:  
Triggers: 
	/*/
//************************************************** MEMBERS ***************************************************
		bool menuView;
		vector <Menu *> stack;
		Menu * previewMenu; 
		Menu loadingScreen;
		Menu titleScreen;
		
//********************************* MEMBER FUNCTIONS *********************************
	
	Menu* BaseStackManager::getNextMenu();
	bool BaseStackManager::isOverlay();
	bool BaseStackManager::hasPreview();	
	bool BaseStackManager:: empty();
	bool BaseStackManager:: aborting();

};
#endif
