#ifndef RENDERING_H
#define RENDERING_H

#include "Component.h"


//********************************* CONSTANTS *********************************
enum EntityType {PROP, PARTICLE, ACTOR};   
//********************************* INITIALIZATION *********************************


class Rendering: public Component  {
public:
	
	Rendering::Rendering();
	Rendering::Rendering(EntityType e, ID id);
	Rendering::Rendering(EntityType e, ID id, ID tex);
	
	EntityType type;
	ID profileIndex; 
	ID texIndex;
	int animIndex;


};


#endif