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
			case SDL_QUIT: G0->gameActive = false; break;
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
			G0->action = true;
		}else if(key < KEYS && key >= 0){
			on(key);
		}
	}
}

// Cycle through key releases and set the key event to false
void BaseInputManager::keyUp(SDL_Keycode key){
	if (key < KEYS && key >= 0) 
		off(key);
	else{
		for (int i = 0; i < D; i++)
			if (key == dArrow[i]){
				specialKeyPressed[i] = false;
			}
	}
}

void BaseInputManager::		clearKeys(){
	for (int key = 0; key < 256; key++){
		for (int i = 0; i < D; i++){
			if (key == dKey[i]){

			}else  
				off(key);
		}
	}
}



//********************************* INPUT RESPONSES *********************************

PlayCommand * BaseInputManager::		checkPause(){
	if (keyPressed[pauseKey]) {
		off(pauseKey);
		if(G0->paused){
			if ( G0->state == TITLE)
				return &stackQuit;	
			else if ( G0->state == PAUSE)				
				return &play;
		}else if(G0->state == PLAY)
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
	if (G0->paused) {
		bool u, d , l, r;
		u = keyPressed[dKey[UP]] || specialKeyPressed[UP];
		d = keyPressed[dKey[DOWN]] || specialKeyPressed[DOWN];
		l = keyPressed[dKey[LEFT]] || specialKeyPressed[LEFT];
		r = keyPressed[dKey[RIGHT]] || specialKeyPressed[RIGHT];

		// add 1-5, R, T, F, C, V, ESC
		if (u){
			cursor.set(0, -1);
			off(dKey[UP]);
			return &cursor;
		}else if (d) {		
			cursor.set(0, 1);
			off(dKey[DOWN]);
			return &cursor;
		}if (l){
			cursor.set(-1, 0);
			off(dKey[LEFT]);
			return &cursor;
		}else if (r){			
			cursor.set(1, 0);
			off(dKey[RIGHT]);
			return &cursor;
		}


		if (G0->action){	
			G0->action = false;
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
void BaseInputManager::		off(SDL_Keycode key){ keyPressed[key] = false; }

XZI BaseInputManager::		mousePos(){
	XZI xz = {mX, mY};
	return xz;
}