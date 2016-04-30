//********************************* INITIALIZATION *********************************
#include "BaseStackManager.h"

BaseStackManager::BaseStackManager(){
	menuView = false;
	previewMenu = NULL;
	initMenus();
}
void BaseStackManager::	init(MenuLoader& loader){
	loader.registerRoot(&loading);
	loader.registerRoot(&title);
}

void BaseStackManager::	initMenus(){
	loadingScreen.setBackground(LOAD);
	loadingScreen.setTimeOut(10);
	titleScreen.setBackground(TITLE);
	titleScreen.setTimeOut(240);
	titleScreen.setFlow(888);

}


//********************************* LOADING *********************************

void BaseStackManager::	loadDefaults(){	
	stack.push_back(&titleScreen);
	stack.push_back(&loadingScreen);
}


void BaseStackManager::setRootMenu(){
	if (G0->screen == PLAY)
		stack.clear();		
	else if (G0->screen == MAIN)	
	{}//stack.push_back(&mainMenu);	
	else if (G0->screen == DLG)	
	{}//	stack.push_back(&dialogMenu);	
	else if (G0->screen == STORE)	
	{}//	stack.push_back(&shopMenu);	
	else if (G0->screen == DBG)	
	{}//	stack.push_back(&debugMenu );	
	//*/
}

void BaseStackManager::update(BaseInputManager &input){
	if (G0->initMenu){
		setRootMenu();		
		G0->initMenu = false;
	}
	if (G0->paused){
		if (empty())	
			loadDefaults();			//pop production bumpers!
		else {
			input.menuInput(stack.back());
			if (aborting()) popMenu();
			else updateMenu();
		}
	}
}


//

void BaseStackManager::setMenu(int menuID){
	if (menuID == 888)
		G0->enterMenu(PLAY);
	else {
		SubMenuType mt = (SubMenuType)menuID;
		if (mt == QUIT)	{
			int i = stack.back()->index; //save for later?
			stack.back()->quit();
		}else if (mt == USE){
			//usageMenu.init(stack.back());
			//stack.push_back(menuList[mt]);
		}else if (mt == PASS){
		} else{
			if (previewMenu == NULL){
				//if (stack.back() != NULL) menuList[mt]->init(stack.back());
				//stack.push_back(menuList[mt]);
			}else{
				if (previewMenu->maxIndex >= 0){
					//stack.push_back(previewMenu);
					//previewMenu = NULL;
				}
			}
		} 		
	}
}
//*/
void BaseStackManager:: updateMenu(){
	if (G0->screen != PLAY){
		Menu *s = stack.back();
		if (s->affirm){
			s->reset();
			setMenu(s->getFlow());
			s = stack.back();
		}
		if (s->update){
			s->refresh();
			if(s->preview){
				SubMenuType mt = (SubMenuType)s->getFlow();
				if (mt != QUIT){
					//previewMenu = menuList[mt];
					//previewMenu->refresh(s->index);
				}else 
					previewMenu = NULL;
			}
			s->update = false;
		} 
	}//*/
}

void BaseStackManager::	pushMenu(Menu * s){
	stack.push_back(s);
}

void BaseStackManager::	popMenu(){
	if (!stack.empty()){
		if (stack.back()->abort){
			stack.back()->reset();
			stack.pop_back();
		}
	}
}



void BaseStackManager::	rapidUpdate(){		
	if (!empty()){
		stack.back()->rapidUpdate();
	}
}

//********************************* DRAW *********************************
void BaseStackManager::	draw(){	
	if (!empty()){
		//drawText();
		//drawCursor();
		//drawIcons();
		drawBackground();
	}
}

void BaseStackManager::	drawHUD(){		
	//M->fontBO.use();	//hudMenu.drawText();
	//M->cursorBO.use();	//hudMenu.drawCursor();
	//M->menuBO.use();	 //hudMenu.drawIcons();
	//hudMenu.drawBackground();
}


void BaseStackManager::	drawText(){
	//M->fontBO.use();	
	//hudMenu.drawDebugConsole();
	stack.back()->drawText();
	if(isOverlay())
		getNextMenu()->drawText();
	if (hasPreview())
		previewMenu->drawText();
}
void BaseStackManager::	drawCursor(){
	//M->cursorBO.use();
	stack.back()->drawCursor();
}
void BaseStackManager::	drawIcons(){
	//M->iconBO.use();
	stack.back()->drawIcons();
	if(isOverlay())
		getNextMenu()->drawIcons();
	if (hasPreview())
		previewMenu->drawIcons();
}
void BaseStackManager::	drawBackground(){
	M->menuBO.use();
	stack.back()->drawBackground();
	if(isOverlay())
		getNextMenu()->drawBackground();
	if (hasPreview())
		previewMenu->drawBackground();
}


//*********************************


void BaseStackManager :: setUp2DView (int width, int height){
	if (!menuView){
		if(width < 1)  width = 1;
		if(height < 1) height = 1;

		glMatrixMode(GL_PROJECTION);
		glPushMatrix();
		glLoadIdentity();
		//gluOrtho2D(0.0, width, 0.0, width);
		glOrtho(0.0, width, 0.0, height, 0, 1);



		menuView = true;
	}
}

void BaseStackManager :: disable2DView ()
{
	if (menuView){
		glMatrixMode(GL_PROJECTION);
		glPopMatrix();

		menuView = false;
		//glMatrixMode(GL_MODELVIEW);
		//glPopMatrix();

	}
}


//*********************************

Menu* BaseStackManager::getNextMenu(){
	int s = stack.size();
	if (s > 1)
		return stack[s-2];
	return NULL;
}

bool BaseStackManager::isOverlay(){
	if (stack.back()->overlay && stack.size() > 1)
		return true;
	return false;
}

bool BaseStackManager::hasPreview(){
	return stack.back()->preview && previewMenu != NULL;
}

bool BaseStackManager:: empty(){
	return stack.empty();
}


bool BaseStackManager:: aborting(){
	return stack.back()->abort;
}