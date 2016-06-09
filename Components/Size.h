#ifndef SIZE_H
#define SIZE_H

#include "Component.h"


//********************************* CONSTANTS *********************************
struct SizeProfile{
	float rad;
	float group;
	float sep;
	float coh;
};
//********************************* INITIALIZATION *********************************


class Size: public Component  {
public:
	Size::Size(){radius = 0;}

	float radius;
	//float box;
	//float scale;



};


#endif