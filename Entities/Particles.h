#ifndef PARTICLES_H
#define PARTICLES_H

#include "Props.h"
#include "../Components/Motion.h"
#include "../Components/Obstacles.h"
//********************************* CONSTANTS *********************************


//********************************* INITIALIZATION *********************************

class Particles : public Props {
	public: 
	Particles::		Particles();


//************************************************** DRAW *************************************************** 

	void Particles ::	refresh (ID id);


//************************************************** MEMBERS ***************************************************
	
	vector<Motion> motion;
	vector<Obstacles> obstacles;
	float delta;

};
#endif