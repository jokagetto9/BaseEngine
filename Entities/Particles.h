#ifndef PARTICLES_H
#define PARTICLES_H

#include "Props.h"
#include "../Components/Motion.h"
#include "../Components/Obstacles.h"
//********************************* CONSTANTS *********************************


//********************************* INITIALIZATION *********************************

class Particles : public Props {
	public: 
		Particles::		Particles(){dict = &particleList;}


//************************************************** DRAW *************************************************** 
	
	virtual void Particles::reserve(ID max);
	void Particles ::	refresh (ID id);
	bool Particles:: add(ID id, Rendering& r, Location& l, Motion &m, Animation &a);
	virtual bool Particles ::canMove (){return true;}

//************************************************** MEMBERS ***************************************************
	 
	vector<Motion> motion;
	vector<Obstacles> obstacles;
	float delta;
	
	static AttackState charge;
};
#endif