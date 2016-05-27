#ifndef ACTORS_H
#define ACTORS_H

#include "Particles.h"
#include "../Components/AI.h"
#include "../../Display/ModelManager.h"
//********************************* CONSTANTS *********************************

const ID P1 = 0;

struct Actor {
	State * st;
	Translation &pos_;
	Motion &mot_;
	AI &ai_;
	//Rendering &ren_;
};

//********************************* INITIALIZATION *********************************

class Actors : public Props{
	public: 
	Actors::	Actors(){}
	void Actors::reserve(ID max);
	void Actors::reset();
	void Actors::reset(ID id);
	
	bool Actors:: add(Rendering& r, Translation& t, Motion &m, Animation &a);


	void Actors::activate(ID id, glm::vec3 pos);
//************************************************** UPDATE ***************************************************
	void Actors ::	update (float physDelta);
	void Actors ::	update (ID id);

	void Actors ::	aiUpdate (float aiDelta);
	void Actors ::	aiUpdate (ID id);

//************************************************** DRAW *************************************************** 

	void Actors ::	refresh (ID id);
	virtual void Actors ::	draw (ID id);	

	Actor Actors::getActor(ID id);
//************************************************** MEMBERS ***************************************************
	
	vector<AI> ai;
	vector<Motion> motion;

	float delta;


	static MotionState walking;
	static AttackState charge;

};
#endif