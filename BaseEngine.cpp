//********************************* INITIALIZATION *********************************
#include "BaseEngine.h"

BaseEngine::	BaseEngine(){	
	initW = false; initC = false; 
	sdlWindow = NULL;			//The window we'll be rendering to
	sdlRenderer = NULL;			//The window renderer
	sdlContext = NULL;			//OpenGL context

	prevTime = glutGet(GLUT_ELAPSED_TIME);	// init start time
	startTime = prevTime;

	frameDelta = 0;	 avgFrameDelta = 0;

	avgFPS = 0;	frameCount = -1;
		
	physLag = 0;		physDelta = 1000/PHYSICS_PERSEC;	// ms per update
	aiLag = 0;			aiDelta = 1000/AI_PERSEC;			// ms per update



}

//********************************* INIT *********************************
bool BaseEngine::initGLAttrib(){
	//framebuffer
	SDL_GL_SetAttribute( SDL_GL_DOUBLEBUFFER, 1 );
	SDL_GL_SetAttribute( SDL_GL_DEPTH_SIZE, 24); 
	//enable framebuffer modes
	SDL_GL_SetAttribute( SDL_GL_ALPHA_SIZE, 1);
	//version
	SDL_GL_SetAttribute( SDL_GL_CONTEXT_MAJOR_VERSION, 3 );
	SDL_GL_SetAttribute( SDL_GL_CONTEXT_MINOR_VERSION, 3 );
	SDL_GL_SetAttribute( SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_COMPATIBILITY );

	//linear filtering
	if( !SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" ) ) {printf( "Warning: Linear texture filtering not enabled!" );}
	return true;
}

bool BaseEngine::initGLEW(){
	glewExperimental = GL_TRUE;
	GLenum status = glewInit(); 
	if (status != GLEW_OK) {cout << "GLEW Error: " << glewGetErrorString(status) << "\n"; exit(1);}
	return true;
	//GLenum error = glGetError(); if (error != GL_NO_ERROR){ 		cout << "OpenGL Error: " << error << " " << gluErrorString(error) << endl;}	
}

bool BaseEngine::initSDL(){
	//init video
	if( SDL_Init( SDL_INIT_VIDEO ) < 0 ) {	 printf( "SDL could not initialize! SDL Error: %s\n", SDL_GetError() ); return false;	}
		
	if(_DEBUG) cout << "Initializing SDL_GL" << endl;
	initGLAttrib(); // init attributes

	//init window
	sdlWindow = SDL_CreateWindow( "Test Window", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, RES.x, RES.z, SDL_WINDOW_SHOWN|SDL_WINDOW_OPENGL );
	if( sdlWindow == NULL ) {	printf( "Window could not be created! SDL Error: %s\n", SDL_GetError() ); 	return false;	}
	initW = true;

	//init context
	sdlContext = SDL_GL_CreateContext(sdlWindow);
	if ( sdlContext == NULL ){printf( "Context could not be created! SDL Error: %s\n", SDL_GetError() );	return false;	}	
	initC = true;
	
	// init SDL_image
	int imgFlags = IMG_INIT_PNG;
	if( !( IMG_Init( imgFlags ) & imgFlags ) ){	printf( "SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError() ); 	return false;	}
	
	//init renderer
	/*/Create vsynced renderer for window
	gRenderer = SDL_CreateRenderer( gWindow, -1, SDL_RENDERER_ACCELERATED );
	if( gRenderer == NULL )	{printf( "Renderer could not be created! SDL Error: %s\n", SDL_GetError() );	return false;	}
	SDL_SetRenderDrawColor( gRenderer, 0x00, 0x0, 0x00, 0xFF ); //*///Initialize renderer color
	
	//if(_DEBUG) cout << "Loading GLEW" << endl;
	initGLEW();

	return true;
}


void BaseEngine::quit(){
	if (initC) SDL_GL_DeleteContext(sdlContext);		sdlRenderer = NULL;
	if (initW) SDL_DestroyWindow( sdlWindow );		sdlWindow = NULL;	
}
//********************************* PRIMARY CYCLES *********************************



//********************************* UPDATES *********************************

void BaseEngine::	trackAVG(){
	float a = frameDelta;
	
	getCurrentTime();
	getFrameDelta(); 	
	if (frameDelta < 16){
		SDL_Delay(16-frameDelta);	
		getCurrentTime();	
		getFrameDelta(); 
	}
	//} while (frameDelta < 16);

	if (avgFrameDelta != 0){
		avgFrameDelta = (avgFrameDelta + a )/2;  
		//avgFrameDelta = (avgFrameDelta + a + frameDelta)/3;  
		avgFrameDelta += frameDelta/2;
	}
	else avgFrameDelta = frameDelta; 
}

void BaseEngine::	trackFPS(){
	if (frameCount >= 1000){
		frameCount = 0;
		startTime = curTime;
	}else {
		frameCount++;
		avgFPS = frameCount / ( (curTime-startTime)  / 1000.f );
	}
}

//********************************* DRAW *********************************


void BaseEngine::displayVersion(){
	if (_DEBUG){
		cout << glGetString(GL_VERSION) << endl;
		cout <<  glGetString(GL_RENDERER) << "  " << glGetString(GL_VENDOR ) << endl << endl;
	}
	logfile << glGetString(GL_VERSION) << endl;
	logfile <<  glGetString(GL_RENDERER) << "  " << glGetString(GL_VENDOR ) << endl << endl;
}

 void BaseEngine::clearDisplay(){
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glMatrixMode(GL_MODELVIEW);	
		glLoadIdentity();	// initialize the selected matrix
}








