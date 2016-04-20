#ifndef BASEENGINE_H
#define BASEENGINE_H


#include "BaseInputManager.h" 
#include "BaseStackManager.h"


//********************************* INITIALIZATION *********************************

class BaseEngine {
public:

	BaseEngine::	BaseEngine();
/*/ Purpose: default constructor /*/
	void BaseEngine::init(BaseInputManager * bInput, BaseStackManager * bStack);

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


//********************************* LOADING *********************************

//********************************* SAVING *********************************

void BaseEngine::		save();	
/*/ Purpose: save game data
Precondition(s): save files exist
Side Effects:  G->save = false
Triggers: H->saveHero(), G->saveState(), spawner.save();
/*/

//********************************* UPDATES *********************************

	
	void BaseEngine::		clockCycle();
/*/ Purpose: ensure phys and ai cycle run at expected cps
Side Effects: G->incLag(), G->prevTime = G->curTime;
Triggers: G->trackTime(), spawner.hourlyUpdate(),
	physicsUpdate(), rapidUpdate()
/*/

	void BaseEngine::		physicsUpdate();
/*/ Purpose: update highp game data at 30 times per second
Side Effects: G->action = false, G->decPhysLag()
Triggers: H->physUpdate(), spawner.collisionDetection()
/*/

	void BaseEngine::		rapidUpdate();
/*/ Purpose: update data at 4 times per second
Side Effects: 	G->decAILag(), freqUpdate()
Triggers: env.aiUpdate()
/*/
	void BaseEngine::	skipTime();

//********************************* DRAW *********************************

	void BaseEngine::display();
/*/ Purpose: display all game elements -> altered by menus 
Precondition(s): once per frame
Side Effects: clear frame buffer bits
Triggers: env.update, env.refreshView(b), C->update(H->pos),
		spawner.drawZones(), H->drawHero(avgfr), menu.draw(),
/*/

	//void BaseEngine::reshape(int w, int h);
	
	void BaseEngine::displayVersion(); /*/
	Side Effects: display opengl and graphics card versions  
	/*/
	

	void BaseEngine::	clearDisplay();
	void BaseEngine ::flush(){ glFlush(); SDL_GL_SwapWindow(sdlWindow); }

//************************************************** MEMBERS ***************************************************


	SDL_Window* sdlWindow;			//The window we'll be rendering to
	SDL_Renderer* sdlRenderer;		//The window renderer
	SDL_GLContext sdlContext;		//OpenGL context


	BaseInputManager * input;
	BaseStackManager * stack;

	bool initW, initC;


};
#endif