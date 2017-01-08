#ifndef COMPONENTS_H
#define COMPONENTS_H

#include "../lib.h"

//********************************* CONSTANTS *********************************
const ID MAX_COMPONENTS = 10000;


struct Identity {
	string name;
	ID index;
	int type;
	int ent; 
};

//********************************* INITIALIZATION *********************************


class Component  {
	public:
};




struct Size  {
	float innerRad;
	float outerRad;
	float sight;
	//vector <boxes>
	//float scale;
};




#endif