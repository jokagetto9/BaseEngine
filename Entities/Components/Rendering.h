#ifndef RENDERING_H
#define RENDERING_H

#include "Component.h"


//********************************* CONSTANTS *********************************

//********************************* INITIALIZATION *********************************


class Rendering: public Component  {
public:
	
	Rendering::Rendering();

	ID tex;
	ID texIndex;
	union {
		int animIndex;
	};


};


#endif