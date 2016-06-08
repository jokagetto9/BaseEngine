//********************************* INITIALIZATION *********************************
#include "BaseGameState.h"
BaseGameState* BaseGameState::instance = 0;
BaseGameState* G;

ofstream logfile;
XZI RES = {800, 600};
ID PIXELSCALE = 4;	

void BaseGameState::init(){

	
	gameActive = true; 
	state = TITLE;
	
	save = false;	load = false; //gload
	action = false;	paused = true;	
	loaded = false;
	actionString = "";
}



//********************************* MEMBER FUNCTIONS *********************************
