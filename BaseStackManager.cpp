//********************************* INITIALIZATION *********************************
#include "BaseStackManager.h"

BaseStackManager::BaseStackManager(){
	menuView = false;
	previewMenu = NULL;
}
void BaseStackManager::	init(MenuLoader& loader){
	loader.registerRoot(&title);
}

//********************************* LOADING *********************************

void BaseStackManager::	loadCommand(PlayCommand * cmd){
	if (cmd) {
		currRoot = cmd;
		cmd->enter(stack, 0);
	}
}

void BaseStackManager::	update(){
	if (empty()){	
		if (G0->state == TITLE){
			title.enter(stack, 1);
			title.enter(stack, 0);			//pop production bumpers!
			currRoot = &title;
		}
	}else {
		if (aborting()) popMenu();
		else updateMenu();
	}
}


void BaseStackManager:: menuInput(MenuCommand * cmd){
	if (!empty())
		cmd->exec(stack.back());
}

//enum GameFunctionCode {BACK, QUIT, SAVE, LOAD, START, OPTN, USE, CNFM, PASS};
void BaseStackManager::setMenu(int flow){
	if (stack.back()->func){
		GameFunctionCode func = (GameFunctionCode)flow;
		if (func == BACK)	{
			int i = stack.back()->index; //save for later?
			stack.back()->quit();
		}else if (func == START){			
			PlayCommand play;
			play.enter(stack, 0);
			currRoot = NULL;
		}else if (func == RESTART){	
			G0->loaded = false;
		}else if (func == QUIT){
			stack.clear();
			G0->loaded = false;
			G0->state = TITLE;
		}else if (func == USE){
			//usageMenu.init(stack.back());
			//stack.push_back(menuList[mt]);
		}
	} else {
		if (currRoot){
			if (currRoot->size() > flow){
				currRoot->enter(stack, flow);
			}
		}
	} 	
}
/*
		if (previewMenu == NULL){
			//if (stack.back() != NULL) menuList[mt]->init(stack.back());
			//stack.push_back(menuList[mt]);
		}else{
			if (previewMenu->maxIndex >= 0){
				//stack.push_back(previewMenu);
				//previewMenu = NULL;
			}
		}
//*/

void BaseStackManager:: updateMenu(){
	if (G0->state != PLAY){
		Menu *s = stack.back();
		if (s->affirm){
			s->reset();
			setMenu(s->getFlow());
		}
		if (!empty()){			
			s = stack.back();
			if (s->update){
				s->refresh();
				if(s->preview){
					GameFunctionCode mt = (GameFunctionCode)s->getFlow();
					if (mt != QUIT){
						//previewMenu = menuList[mt];
						//previewMenu->refresh(s->index);
					}else 
						previewMenu = NULL;
				}
				s->update = false;
			} 
		}
	}//*/
}

void BaseStackManager::	pushMenu(Menu * s){
	stack.push_back(s);
}

void BaseStackManager::	popMenu(){
	if (!stack.empty()){
		if (stack.back()->abort){
			if (stack.size() == 1 && G0->state != TITLE)							
				stack.back()->abort = false;
			else{
				stack.back()->reset();
				stack.pop_back();
			}
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
		drawCursor();
		//drawIcons();
		drawBackground();
	}
}

void BaseStackManager::	drawHUD(){		
	//M->fontBO.use();		//hudMenu.drawText();
	//M->cursorBO.use();	//hudMenu.drawCursor();
	//M->menuBO.use();		//hudMenu.drawIcons();
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
	M->cursorBO.use();
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

bool BaseStackManager:: backdrop(){
	if ( !stack.empty())
		return stack.back()->backdrop;
	else
		return true;
}
