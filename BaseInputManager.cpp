//********************************* INITIALIZATION *********************************
#include "BaseInputManager.h"

void BaseInputManager::init(){
	for (int i = 0; i < 256; i++) keyPressed[i] = false;		
	for (int i = 0; i < 20; i++) specialKeyPressed[i] = false;
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
				//G->mX = ev.motion.x/PIXELSCALE;
				//G->mY = ev.motion.y/PIXELSCALE;
				break;
			case SDL_MOUSEBUTTONDOWN:
				//H->laserOn();
				break;
			case SDL_MOUSEBUTTONUP:				
				//H->laserOff();
				break;
}	}	}


// Cycle through key presses and set the key event to true
void BaseInputManager::keyDown(SDL_Keycode key){
	//quick actions 
	if (key == SDLK_w || key == SDLK_s || key == SDLK_a || key == SDLK_d) on(key);
	else switch (key){		
		case SDLK_UP: specialKeyPressed[UP] = true; break;
		case SDLK_DOWN: specialKeyPressed[DOWN] = true; break;
		case SDLK_LEFT: specialKeyPressed[LEFT] = true; break;
		case SDLK_RIGHT: specialKeyPressed[RIGHT] = true; break;	
		case SDLK_LSHIFT: specialKeyPressed[5] = true; break;	
		default: break;
    }
	if (key == SDLK_e)	{
		G0->action = true;
	}	
}

// Cycle through key releases and set the key event to false
void BaseInputManager::keyUp(SDL_Keycode key){
	// disable directions on lift
	if (key == SDLK_w || key == SDLK_s || key == SDLK_a || key == SDLK_d) {
		off(key); //halt = false; //spinning camera
	}else if (key < 256 && key >= 0) on(key);		//activate regular keys
	else switch (key){		
		case SDLK_UP: specialKeyPressed[UP] = false; break;
		case SDLK_DOWN: specialKeyPressed[DOWN] = false; break;
		case SDLK_LEFT: specialKeyPressed[LEFT] = false; break;
		case SDLK_RIGHT: specialKeyPressed[RIGHT] = false; break;	
		case SDLK_LSHIFT: specialKeyPressed[5] = false; 		
			break;	
		default: break;
    }
}

void BaseInputManager::		clearKeys(){
	for (int key = 0; key < 256; key++){
		if (key == SDLK_w || key == SDLK_s || key == SDLK_a || key == SDLK_d || key == SDLK_e) {
			//off(key); //stop = false;
		}else if (key < 256 && key >= 0) off(key);
	}
}



//********************************* INPUT RESPONSES *********************************

void BaseInputManager::		checkToggles(){
	//toggles
	if (keyPressed[SDLK_ESCAPE])			G0->gameActive = false; 
}



//********************************* MENU *********************************


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
