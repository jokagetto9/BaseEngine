#ifndef BASEGAMESTATE_H
#define BASEGAMESTATE_H

#include "../../lib.h"
//********************************* CONSTANTS *********************************

const float PHYSICS_PERSEC = 20.0f;		// per second
const float AI_PERSEC =  4.0f;			// per second
const float MAXFPS = 60.0f;				// phys + ai are limited to 60 fps


class BaseGameState {
public:
	
	BaseGameState::BaseGameState(){}
	void BaseGameState::		init();	
/*/ Purpose: init members
Side Effects:  set prevTime, startTime
Triggers: loadState
/*/
	void BaseGameState::		quit(){}
/*/ Purpose: close game state 
Side Effects:  deletes instance
/*/
	
//********************************* LOADING *********************************

	void BaseGameState::	loadState(){}
/*/ Purpose: load game state data from gs.txt
Precondition(s): gs.txt has valid data
Side Effects: loads days, minutes
/*/

//********************************* SAVING *********************************

	void BaseGameState::	saveState(){}
/*/ Purpose: save game state data to gs.txt
Precondition(s): file exists
Side Effects:  Saves days, minutes
/*/

//************************************************** MEMBERS ***************************************************

		
		GameStateCode state;
		bool save,  load; 
		bool gameActive;//
		bool paused;
		bool action;
		
		string actionString;



};

extern BaseGameState* G0;
#endif