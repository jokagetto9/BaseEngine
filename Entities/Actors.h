#ifndef ACTORS_H
#define ACTORS_H

#include "Particles.h"
#include "../Components/Target.h"
//********************************* CONSTANTS *********************************


struct Actor {
	State * st;
	Location &pos_;
	Motion &mot_;
	Target &tar_;
	//Rendering &ren_;
};

//********************************* INITIALIZATION *********************************

class Actors : public Particles{
	public: 
	Actors::	Actors(){}
	void Actors::reserve(ID max);
	void Actors::reset();
	void Actors::reset(ID id);
	
	bool Actors:: add(Rendering& r, Location& l, Motion &m, Animation &a);


	void Actors::activate(ID id, glm::vec3 pos);
	void Actors::activateAll(glm::vec3 pos);
//************************************************** UPDATE ***************************************************
	void Actors ::	update (float physDelta);
	void Actors ::	update (ID id);

	void Actors ::	aiUpdate (float aiDelta);
	void Actors ::	aiUpdate (ID id);

	Actor Actors::getActor(ID id);
//************************************************** MEMBERS ***************************************************
	
	vector<Target> target;


	static MotionState walking;
	static AttackState charge;

};
#endif