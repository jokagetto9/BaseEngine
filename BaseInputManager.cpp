//********************************* INITIALIZATION *********************************
#include "BaseInputManager.h"

void BaseInputManager::init(){
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
	for (int i = 0; i < D; i++){
		if (key == dKey[i]){
			on(key);
			i = D;
		}else if (key == dArrow[i]){
			specialKeyPressed[i] = true;
			i = D;
		}
	}
	if (key == SDLK_e)	{
		G0->action = true;
	}	
}

// Cycle through key releases and set the key event to false
void BaseInputManager::keyUp(SDL_Keycode key){
	bool move = false;
	for (int i = 0; i < D && !move; i++){
		if (key == dKey[i]){
			off(key); //halt = false; //spinning camera
			move = true;
		}else if (key == dArrow[i]){
			specialKeyPressed[i] = false;
			move = true;
		}
	}
	if (!move && key < KEYS && key >= 0) 
		on(key);
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

void BaseInputManager::		checkToggles(){
	if (keyPressed[SDLK_ESCAPE])			G0->gameActive = false; 
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

void BaseInputManager::		menuInput(Menu *screen){
	if (G0->paused) {
		// add 1-5, R, T, F, C, V, ESC
		if (keyPressed[SDLK_w] || specialKeyPressed[UP]){ 
			keyPressed[SDLK_w] = false; specialKeyPressed[UP] = false;
			screen->cursorUD(-1);
		}else if (keyPressed[SDLK_s] || specialKeyPressed[DOWN]){ 
			keyPressed[SDLK_s] = false; specialKeyPressed[DOWN] = false;
			screen->cursorUD(1);
		}else if (keyPressed[SDLK_a] || specialKeyPressed[LEFT]){ 
			keyPressed[SDLK_a] = false; specialKeyPressed[LEFT] = false;
			screen->cursorLR(-1);
		}else if (keyPressed[SDLK_d] || specialKeyPressed[RIGHT]){ 
			keyPressed[SDLK_d] = false; specialKeyPressed[RIGHT] = false;
			screen->cursorLR(1);
		}
		if (G0->action){//(keyPressed[SDLK_e]) {
			screen->enter();	
			G0->action = false;
			//off(SDLK_e);
		} else if (keyPressed[SDLK_q]) {
			screen->quit();	
			off(SDLK_q);
		}
	}
} //*/
//********************************* MEMBER FUNCTIONS *********************************


void BaseInputManager::		on(SDL_Keycode key){ keyPressed[key] = true ; }
void BaseInputManager::		off(SDL_Keycode key){ keyPressed[key] = false; }

XZI BaseInputManager::		mousePos(){
	XZI xz = {mX, mY};
	return xz;
}