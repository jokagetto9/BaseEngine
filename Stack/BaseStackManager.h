#ifndef BASESTACKMANAGER_H
#define BASESTACKMANAGER_H

#include "../BaseInputManager.h"
#include "BaseMenuLoader.h"


//********************************* CONSTANTS *********************************

//********************************* INITIALIZATION *********************************

class BaseStackManager {
public:
	BaseStackManager::BaseStackManager();
	// Constructor
	void BaseStackManager::	init(BaseMenuLoader& loader);	
	
	void BaseStackManager::	loadCommand(PlayCommand * cmd);
	
	void BaseStackManager::	updateMenu();
	void BaseStackManager::	update();
	
	virtual void BaseStackManager::setMenu(int flow);
	void BaseStackManager:: menuInput(MenuCommand * cmd);

	void BaseStackManager::	pushMenu(Menu * s);
	void BaseStackManager::	popMenu();
		
	void BaseStackManager::	rapidUpdate();
	
//********************************* DRAW *********************************
	void BaseStackManager::	draw();
	virtual void BaseStackManager::	drawHUD();
	void BaseStackManager::	drawMenus();
	void BaseStackManager::	drawText();
	
	void BaseStackManager::	drawCursor();
	void BaseStackManager::	drawIcons();
	void BaseStackManager::	drawBackground();

	 

	void BaseStackManager::	setUp2DView(int width, int height);
	void BaseStackManager::	disable2DView();


//************************************************** MEMBERS ***************************************************
		bool menuView;
		int index;
		vector <Menu *> stack;
		Menu * previewMenu; 
		PlayCommand * currRoot; 
		StackCommand title;
		
//********************************* MEMBER FUNCTIONS *********************************
	
	Menu* BaseStackManager::getNextMenu();
	bool BaseStackManager::isOverlay();
	bool BaseStackManager::hasPreview();	
	bool BaseStackManager:: empty();
	bool BaseStackManager:: aborting();
	bool BaseStackManager:: backdrop();

};
#endif
