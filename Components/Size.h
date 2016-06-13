#ifndef SIZE_H
#define SIZE_H

#include "Component.h"


//********************************* CONSTANTS *********************************

//********************************* INITIALIZATION *********************************


class Size: public Component  {
public:
	Size::Size(){ id= 0; scale = 1;}
	Size::Size(ID i, float s){ id = i; scale = s; }

	ID id;
	float scale;
	//float box;
	//float scale;



};


#endif