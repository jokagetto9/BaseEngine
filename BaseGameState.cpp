//********************************* INITIALIZATION *********************************
#include "BaseGameState.h"
//BaseGameState* BaseGameState::instance = 0;
BaseGameState* G0;

ofstream logfile;
XZI RES = {800, 600};


void BaseGameState::init(){

	
	gameActive = true; 
	state = TITLE;
	
	save = false;	load = false; //gload
	action = false;	paused = true;	

	actionString = "";
}



//********************************* MEMBER FUNCTIONS *********************************

//
void BaseGameState::enterMenu(GameStateCode code){
	state = code; 
	if (code == PLAY) {
		paused = false; 
	} else	
		paused = true;	
}//*/
