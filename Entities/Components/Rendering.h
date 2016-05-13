#ifndef RENDERING_H
#define RENDERING_H

#include "Component.h"
#include "../../../Display/Animation.h"


//********************************* CONSTANTS *********************************

//********************************* INITIALIZATION *********************************


class Rendering: public Compoment  {
public:
	
	Rendering::Rendering();
		Animation walkAnim;
};


#endif