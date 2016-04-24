//********************************* INITIALIZATION *********************************
#include "BaseGameState.h"
//BaseGameState* BaseGameState::instance = 0;
BaseGameState* G0;

ofstream logfile;
XZI RES = {800, 600};


void BaseGameState::init(){
	prevTime = glutGet(GLUT_ELAPSED_TIME);	// init start time
	startTime = prevTime;

	frameDelta = 0;	 avgFrameDelta = 0;

	avgFPS = 0;	frameCount = -1;
		
	physLag = 0;		physDelta = 1000/PHYSICS_PERSEC;	// ms per update
	aiLag = 0;			aiDelta = 1000/AI_PERSEC;			// ms per update

	
	gameActive = true; 
	
	
	save = false;	load = false; //gload
	action = false;	paused = true;	
	initMenu = false; updateMenu = false;
	blackDrop = true;

	fog = true; 

	actionString = "";
}



//********************************* UPDATES *********************************

void BaseGameState::	trackAVG(){
	float a = frameDelta;
	
		getCurrentTime();
		getFrameDelta(); 
		/*/
		if (frameDelta < 16){
			SDL_Delay(16-frameDelta);	
			getCurrentTime();	
			getFrameDelta(); 
		}//*/

	if (avgFrameDelta != 0){
		avgFrameDelta = (avgFrameDelta + a )/2;  
		//avgFrameDelta = (avgFrameDelta + a + frameDelta)/3;  
		avgFrameDelta += frameDelta/2;
	}
	else avgFrameDelta = frameDelta; 
}

void BaseGameState::	trackFPS(){
	if (frameCount >= 1000){
		frameCount = 0;
		startTime = curTime;
	}else {
		frameCount++;
		avgFPS = frameCount / ( (curTime-startTime)  / 1000.f );
	}
}

//********************************* MEMBER FUNCTIONS *********************************

//
void BaseGameState::enterMenu(RootMenuType root){
	screen = root; 
	initMenu = true;
	updateMenu = true;
	if (root == PLAY) {
		paused = false; 
	} else	
		paused = true;	
}//*/

void BaseGameState::togglePause(){
	if (paused) {
		paused = false; initMenu = false;
	} else
		paused = true;	
}
