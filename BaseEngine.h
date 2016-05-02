#ifndef BASEENGINE_H
#define BASEENGINE_H


#include "BaseInputManager.h" 
#include "Stack/BaseStackManager.h"


//********************************* INITIALIZATION *********************************

class BaseEngine {
public:

	BaseEngine::	BaseEngine();
/*/ Purpose: default constructor /*/

	bool initGLAttrib(); /*/
	Purpose: Load SDL_GL attributes 
	Returns: true if nothing fails
	Side Effects:  Initializes framebuffer, enables, depthbuffer, version, linear filtering 
	/*/
 
	bool initGLEW(); /*/
	Purpose: init GLEW  
	Returns: true if nothing fails
	Side Effects:  Initializes GL extensions
	/*/

	bool initSDL(); /*/
	Purpose: Load SDL window using OpenGL 
	Parameter(s): N/A
	Precondition(s): N/A
	Returns: true if nothing fails
	Side Effects:  Initializes SDL_Window, SDL_GL Context, SDL_image
	Triggers: initGLAttrib, initGLEW, displayVersion
	/*/



	void BaseEngine::	quit(); 
/*/ Purpose: close engine 
Triggers: spawner.quit()
/*/
	
//********************************* UPDATES *********************************
	
	void BaseEngine::		trackAVG();
/*/ Purpose: track avgFrameDelta from animations
Precondition(s): avgFrameDelta must be initialized
Side Effects: avgFrameDelta = (avgFrameDelta + prevFrameDelta + curFrameDelta)/3
/*/

	void BaseEngine::		trackFPS();
/*/ Purpose: track avgFPS for display
Precondition(s): game has been running a few seconds
Side Effects: frameCount++
/*/
//********************************* MEMBER FUNCTIONS *********************************
	
	void BaseEngine::displayVersion(); /*/
	Side Effects: display opengl and graphics card versions  
	/*/

	void BaseEngine::		getCurrentTime(){curTime = glutGet(GLUT_ELAPSED_TIME);}
/*/ Purpose: update current time
Side Effects: curTime = system time
/*/

	void BaseEngine::		getFrameDelta(){frameDelta = curTime - prevTime;}
/*/ Purpose: get new frame delta
Precondition(s): curTime and prevTime are initialized
Side Effects: frameDelta = ms from prev to cur frame
/*/

	void BaseEngine::		incLag(){ physLag += frameDelta; aiLag += frameDelta; }
/*/ Purpose: increase phys and ai lag
Side Effects: physLag and aiLag increase by frameDelta
/*/

	void BaseEngine::		decPhysLag(){ physLag -= physDelta;	}
/*/ Purpose: decrease physlag by phys cycle time
Precondition(s): phys cycle has just completed
Side Effects: physLag is decreased by (30/1000)ms
/*/

	void BaseEngine::		decAILag(){	aiLag -= aiDelta; }
/*/ Purpose: decrease ailag by ai cycle time
Precondition(s): ai cycle has just completed
Side Effects: aiLag is decreased by 250ms
/*/

	bool BaseEngine::		testLag(){ return physLag > physDelta || aiLag > aiDelta; }
/*/ Purpose: determine if phys or ai lag is large enough to run cycle
Returns: true is flag is > then cycle delta
/*/

	bool BaseEngine::		lagVSlag(){	return physLag - physDelta > aiLag - aiDelta; }
/*/ Purpose: determine which lag is larger
Returns: true if physLag > aiLag
/*/


	void BaseEngine ::flush(){ glFlush(); SDL_GL_SwapWindow(sdlWindow); }
	
	void BaseEngine::	clearDisplay();


//************************************************** MEMBERS ***************************************************


	SDL_Window* sdlWindow;			//The window we'll be rendering to
	SDL_Renderer* sdlRenderer;		//The window renderer
	SDL_GLContext sdlContext;		//OpenGL context


	BaseInputManager * input;
	BaseStackManager * stack;

	bool initW, initC;
	
		long prevTime;			//cpu time at the start of the prev frame
		long curTime;			//cpu time at the start of the current frame
		GLuint startTime;		//arbitrary start time for measuring fps

		float frameDelta;			//ms per frame
		float avgFrameDelta;		//avg ms per frame !!!number is halved!!!
	
		float avgFPS;				//approximate fps for display
		int frameCount;				//frame count for fps calc
		long physLag, aiLag;		//remaining ms for physics updates
		float physDelta, aiDelta;	// CONST ms per update	

};
#endif