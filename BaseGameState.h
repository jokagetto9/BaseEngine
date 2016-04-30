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

//********************************* UPDATES *********************************
	
	void BaseGameState::		trackAVG();
/*/ Purpose: track avgFrameDelta from animations
Precondition(s): avgFrameDelta must be initialized
Side Effects: avgFrameDelta = (avgFrameDelta + prevFrameDelta + curFrameDelta)/3
/*/

	void BaseGameState::		trackFPS();
/*/ Purpose: track avgFPS for display
Precondition(s): game has been running a few seconds
Side Effects: frameCount++
/*/
	void BaseGameState::enterMenu(GameStateCode code);

//************************************************** MEMBERS ***************************************************

		long prevTime;			//cpu time at the start of the prev frame
		long curTime;			//cpu time at the start of the current frame
		GLuint startTime;		//arbitrary start time for measuring fps

		float frameDelta;			//ms per frame
		float avgFrameDelta;		//avg ms per frame !!!number is halved!!!
	
		float avgFPS;				//approximate fps for display
		int frameCount;				//frame count for fps calc
		long physLag, aiLag;		//remaining ms for physics updates
		float physDelta, aiDelta;	// CONST ms per update	
		
		GameStateCode state;
		bool save,  load; 
		bool gameActive;//
		bool paused;
		bool action;
		
		string actionString;

//********************************* MEMBER FUNCTIONS *********************************
	
	void BaseGameState::		getCurrentTime(){curTime = glutGet(GLUT_ELAPSED_TIME);}
/*/ Purpose: update current time
Side Effects: curTime = system time
/*/

	void BaseGameState::		getFrameDelta(){frameDelta = curTime - prevTime;}
/*/ Purpose: get new frame delta
Precondition(s): curTime and prevTime are initialized
Side Effects: frameDelta = ms from prev to cur frame
/*/

	void BaseGameState::		incLag(){ physLag += frameDelta; aiLag += frameDelta; }
/*/ Purpose: increase phys and ai lag
Side Effects: physLag and aiLag increase by frameDelta
/*/

	void BaseGameState::		decPhysLag(){ physLag -= physDelta;	}
/*/ Purpose: decrease physlag by phys cycle time
Precondition(s): phys cycle has just completed
Side Effects: physLag is decreased by (30/1000)ms
/*/

	void BaseGameState::		decAILag(){	aiLag -= aiDelta; }
/*/ Purpose: decrease ailag by ai cycle time
Precondition(s): ai cycle has just completed
Side Effects: aiLag is decreased by 250ms
/*/

	bool BaseGameState::		testLag(){ return physLag > physDelta || aiLag > aiDelta; }
/*/ Purpose: determine if phys or ai lag is large enough to run cycle
Returns: true is flag is > then cycle delta
/*/

	bool BaseGameState::		lagVSlag(){	return physLag - physDelta > aiLag - aiDelta; }
/*/ Purpose: determine which lag is larger
Returns: true if physLag > aiLag
/*/

	void BaseGameState::		togglePause();	
/*/ Purpose: toggle debug text
Side Effects:  cons -> false, !cons -> true
/*/



};

extern BaseGameState* G0;
#endif