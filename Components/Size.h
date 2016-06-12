#ifndef SIZE_H
#define SIZE_H

#include "Component.h"


//********************************* CONSTANTS *********************************

//********************************* INITIALIZATION *********************************


class Size: public Component  {
public:
	Size::Size(){scale = 1; id= 0;}

	float scale;
	ID id;
	//float box;
	//float scale;



};


#endif