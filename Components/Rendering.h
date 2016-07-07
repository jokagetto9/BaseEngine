#ifndef RENDERING_H
#define RENDERING_H

#include "Component.h"


//********************************* CONSTANTS *********************************

//********************************* INITIALIZATION *********************************


class Rendering: public Component  {
public:
	
	Rendering::Rendering(){	tex = 0;	texIndex = 0;	}
	Rendering::Rendering(ID t, ID id)
		{	tex = t;	texIndex = id;	}

	ID tex; 
	int texIndex;
	int baseIndex;
};

#endif