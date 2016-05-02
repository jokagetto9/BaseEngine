//********************************* INITIALIZATION *********************************
#include "BaseInputManager.h"

void BaseInputManager::init(MenuLoader& loader){	
	loader.registerRoot(&pause);
	for (int i = 0; i < KEYS; i++) keyPressed[i] = false;		
	for (int i = 0; i < SKEYS; i++) specialKeyPressed[i] = false;
	mouseR = false; mouseL = false;
	movecmd.o = STOP;
	dKey[0] = SDLK_a;
	dKey[1] = SDLK_d;
	dKey[2] = SDLK_w;
	dKey[3] = SDLK_s;
	dArrow[0] = SDLK_LEFT;
	dArrow[1] = SDLK_RIGHT;
	dArrow[2] = SDLK_UP;
	dArrow[3] = SDLK_DOWN;
	pauseKey = SDLK_ESCAPE;
	actionKey = SDLK_e;
	cancelKey = SDLK_q;
	//backKey
}


//********************************* KEY CYCLE *********************************


void BaseInputManager::pollKeyEvents(){
	SDL_Keycode key;
	while(SDL_PollEvent(&ev)){
		key = ev.key.keysym.sym;
		switch (ev.type){
			case SDL_QUIT: G->gameActive = false; break;
			case SDL_KEYDOWN: keyDown(key); break; // Handle key presses     
			case SDL_KEYUP: keyUp(key); break;
			case SDL_MOUSEMOTION : 				
				mX = ev.motion.x/PIXELSCALE;
				mY = ev.motion.y/PIXELSCALE;
				break;
			case SDL_MOUSEBUTTONDOWN:
				mouseL = true;				break;
			case SDL_MOUSEBUTTONUP:	
				mouseL = false;				break;
}	}	}


// Cycle through key presses and set the key event to true
void BaseInputManager::keyDown(SDL_Keycode key){
	//quick actions 
	bool move = false;
	for (int i = 0; i < D && !move; i++){
		if (key == dKey[i]){
			on(key);
			move = true;
		}else if (key == dArrow[i]){
			specialKeyPressed[i] = true;
			move = true;
		}
	}
	if (!move){
		if (key == actionKey)	{
			G->action = true;
		}else if(key < KEYS && key >= 0){
			on(key);
		}
	}
}

// Cycle through key releases and set the key event to false
void BaseInputManager::keyUp(SDL_Keycode key){
	off(key);
	if (key == actionKey)		
		G->action = false;
}


//********************************* INPUT RESPONSES *********************************

PlayCommand * BaseInputManager::		checkPause(){
	if (keyPressed[pauseKey]) {
		off(pauseKey);
		if(G->paused){
			if ( G->state == TITLE)
				G->gameActive = false;
			else if ( G->state == PAUSE)				
				return &play;
		}else if(G->state == PLAY)
			return &pause;
		return NULL;
	}
	return NULL;
}



//********************************* MENU *********************************


MoveCommand * BaseInputManager::		directionInput(){
	bool u, d , l, r;
	u = keyPressed[dKey[UP]];
	d = keyPressed[dKey[DOWN]];
	l = keyPressed[dKey[LEFT]];
	r = keyPressed[dKey[RIGHT]];
	if (u && l)			movecmd.o = UL;		
	else if (u && r)	movecmd.o = UR;
	else if (u)			movecmd.o = UP;
	else if (d && l)	movecmd.o = DL;
	else if (d && r)	movecmd.o = DR;
	else if (d)			movecmd.o = DOWN;
	else if (l)			movecmd.o = LEFT;
	else if (r)			movecmd.o = RIGHT;
	else				
		movecmd.o = STOP;
	return &movecmd;
}

Command * BaseInputManager::		mouseInput(){
	return NULL;
}

MenuCommand *  BaseInputManager::	menuInput(){
	if (G->paused) {
		bool u = false; bool d = false; 
		bool l = false; bool r = false;
		if (keyPressed[dKey[UP]]){
			off(dKey[UP]); u = true;
		} else if ( specialKeyPressed[UP]){
			off(dArrow[UP]); u = true;
		} else if (keyPressed[dKey[DOWN]]){
			off(dKey[DOWN]); d = true;
		} else if ( specialKeyPressed[DOWN]){
			off(dArrow[DOWN]); d = true;
		} else if (keyPressed[dKey[LEFT]]){
			off(dKey[LEFT]); l = true;
		} else if ( specialKeyPressed[LEFT]){
			off(dArrow[LEFT]); l = true;
		} else if (keyPressed[dKey[RIGHT]]){
			off(dKey[RIGHT]); r = true;
		} else if ( specialKeyPressed[RIGHT]){
			off(dArrow[RIGHT]); r = true;
		}
		if (u){
			cursor.set(0, -1);
			return &cursor;
		}else if (d) {		
			cursor.set(0, 1);
			return &cursor;
		}if (l){
			cursor.set(-1, 0);
			return &cursor;
		}else if (r){			
			cursor.set(1, 0);
			return &cursor;
		}


		if (G->action){	
			G->action = false;
			return &menucnfm;
		} else if (keyPressed[cancelKey]) {
			off(cancelKey);
			return &menuquit;
		}
	}
	return &null;
} //*/
//********************************* MEMBER FUNCTIONS *********************************


void BaseInputManager::		on(SDL_Keycode key){ keyPressed[key] = true ; }
void BaseInputManager::		off(SDL_Keycode key){ 
	if (key < KEYS && key >= 0) 
		keyPressed[key] = false; 
	else 
		for (int i = 0; i < D; i++)
			if (key == dArrow[i]){
				specialKeyPressed[i] = false;
				i = D;
			}	

}

XZI BaseInputManager::		mousePos(){
	XZI xz = {mX, mY};
	return xz;
}