//********************************* INITIALIZATION *********************************
#include "BaseGameState.h"
GameState* GameState::instance = 0;
GameState* G;

ofstream logfile;
XZI RES = {800, 600};


void BaseGameState::init(){

	
	gameActive = true; 
	state = TITLE;
	
	save = false;	load = false; //gload
	action = false;	paused = true;	
	loaded = false;
	actionString = "";
}



//********************************* MEMBER FUNCTIONS *********************************
