#ifndef SIZE_H
#define SIZE_H

#include "Component.h"


//********************************* CONSTANTS *********************************

//********************************* INITIALIZATION *********************************


class Size: public Component  {
public:
	Size::Size(){ colR = 0; sepR = 0; avoR = 0;}
	Size::Size(float c, float s, float a){ colR = c; sepR = s; avoR = a;}

	float colR;
	float sepR;
	float avoR;
	//float box;
	//float scale;



};


#endif