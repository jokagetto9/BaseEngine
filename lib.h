#ifndef LIB_H
#define LIB_H

#define GLEW_STATIC
#include "gl/glew.h"
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
//#include <cassert>
#include <string>
#include <sstream>
#include <iostream>
#include <fstream>
#include <list>
#include <vector>
#include "gl/glut.h"

#include "sdl/SDL.h"
#include "sdl/SDL_image.h"
//#include <SDL_ttf.h>
#include "sdl/SDL_opengl.h"


#include <glm/glm.hpp>
#include <glm/gtx/norm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "rapidxml/rapidxml_utils.hpp"

using namespace std;

typedef GLuint ID;

struct XZI {int x, z;};

extern ofstream logfile;

extern XZI RES;

const double pi = glm::pi<double>();


	extern ID PIXELSCALE;			// 14x10	// 16x12
	const int pWIDTH = 256;	// 224;		// 256;		
	const int pHEIGHT = 192;	// 160;		// 192;
	const float ASPECTR = (float)pWIDTH / (float)pHEIGHT; // pov ratio

	const float PERSPECTIVE = 60.0f;	

	//camera turn per frame
	const float TURN_RATE = 0.15f; //pan rate
	const float ZOOM_RATE = 0.00025f; //zoom rate

//menu indices
enum GameStateCode {PAUSE, TITLE, PLAY, DBG };
enum GameFunctionCode {BACK, SAVE, LOAD, START, RESTART, OPTN, USE, CNFM, PASS, MAINMENU, QUIT};
//from other games
//enum LaserMenuCommand {EXIT, TITLE, OPTN, STGSLCT, STGINFO, STGCOMP, UPGRADE, PLAY};
//enum PrimeMenuCommand {PLAY, EXIT, TITLE, MAIN, SYS, STORE, DLG, DBG }; //when not exit
//enum MenuType {QUIT, STAT, EQP, INV, LOOT, RELIC, SKLS, JRNL, ACTIVEEQP, ACTIVEITM, USE, SHOPEQP, SHOPLOOT, CNFM, NUMSLCT, PASS};
//********************************* DIMENSIONS AND DIRECTIONS *********************************


enum Drctn {WEST, EAST, NORTH, SOUTH, NW, NE, SW, SE, DUNNO};
enum Oriet {LEFT, RIGHT, UP, DOWN,  UL, UR, DL, DR, STOP}; 

const XZI ADJ_ [] = {
	{-1, 0}, {1, 0}, {0, -1}, {0, 1},		{-1, -1}, {1, -1}, {-1, 1}, {1, 1}, 	{-2, 0}, {2, 0}, {0, -2}, {0, 2},		
	{-2, -1}, {-2, -2}, {-1, -2},		{2, -1}, {2, -2}, {1, -2},		{-2, 1}, {-2, 2}, {-1, 2},			{2, 1}, {2, 2}, {1, 2}
};
const Drctn D_DIA [][2] = {{NORTH, WEST}, {NORTH, EAST}, {SOUTH, WEST}, {SOUTH, EAST}};  
const Drctn D_OPP [] = {EAST, WEST, SOUTH, NORTH, SE, SW, NE, NW};
const Drctn D_CORNER [] = {WEST, EAST, NORTH, SOUTH, NORTH, EAST, WEST, SOUTH, DUNNO};
const float D_ROTATE [] = {90, -90, 0, -180, 45, -45, 135, -135};
const Drctn D_R [] = {NORTH, SOUTH, WEST, EAST, SE, SW, NE, NW};
const Drctn D_X [][2] = {{NE, SE}, {SW, NW}, {SW, SE}, {NE, NW}};  

//********************************* CONSTANTS *********************************
// mod 2x2 = 0-3 
const XZI G4_0 = {0, 0}; const XZI G4_1 = {1, 0};
const XZI G4_2 = {0, 1}; const XZI G4_3 = {1, 1};
const XZI G4__[] = {G4_2, G4_3, G4_0, G4_1,};
//mod 4x4 = 0-15
const XZI G16_2 = {2, 0};	const XZI G16_3 = {3, 0};
const XZI G16_6 = {2, 1};	const XZI G16_7 = {3, 1};
const XZI G16_8 = {0, 2};	const XZI G16_9 = {1, 2};
const XZI G16_10 = {2, 2};	const XZI G16_11 = {3, 2};
const XZI G16_12 = {0, 3};	const XZI G16_13 = {1, 3}; 
const XZI G16_14 = {2, 3};	const XZI G16_15 = {3, 3};
const XZI G25_4 = {4, 0};	const XZI G25_9 = {4, 1};
const XZI G25_14 = {4, 2};	const XZI G25_19 = {4, 3};
const XZI G25_20 = {0, 4};	const XZI G25_21 = {1, 4};
const XZI G25_22 = {2, 4};	const XZI G25_23 = {3, 4};
const XZI G25_24 = {4, 4};



const XZI G16__[] = {	G16_12, G16_13, G16_14, G16_15, 
						G16_8, G16_9, G16_10, G16_11,  
						G4_2, G4_3, G16_6, G16_7, 
						G4_0, G4_1, G16_2, G16_3 
					}; 


const XZI G25__[] = {	G25_20, G25_21, G25_22, G25_23, G25_24,
						G16_12, G16_13, G16_14, G16_15, G25_19,
						G16_8, G16_9, G16_10, G16_11, G25_14,
						G4_2, G4_3, G16_6, G16_7, G25_9,
						G4_0, G4_1, G16_2, G16_3, G25_4,
					}; 

#endif
