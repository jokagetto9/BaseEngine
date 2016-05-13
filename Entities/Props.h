#ifndef PROPS_H
#define PROPS_H

#include "Components\Rendering.h"
#include "Components\Translation.h"
//********************************* CONSTANTS *********************************


//********************************* INITIALIZATION *********************************

class Props {
	public: 
	Props::		Props();
	Props ::	Props (ID reserve);


	vector<Rendering> rendering;
	vector<Translation> translation;

};
#endif