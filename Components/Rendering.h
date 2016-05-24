#ifndef RENDERING_H
#define RENDERING_H

#include "Component.h"


//********************************* CONSTANTS *********************************

//********************************* INITIALIZATION *********************************


class Rendering: public Component  {
public:
	
	Rendering::Rendering(){	tex = 0;	texIndex = 0;	animIndex = -1;	}
	Rendering::Rendering(ID t, ID id)
		{	tex = t;	texIndex = id;	animIndex = -1;	}

	ID tex; 
	ID texIndex;
	int animIndex;
};

#endif