#ifndef ACTORS_H
#define ACTORS_H

#include "Particles.h"
#include "../Components/Target.h"
#include "../Components/Obstacles.h"
#include "../../Display/ModelManager.h"
//********************************* CONSTANTS *********************************


struct Actor {
	State * st;
	Location &pos_;
	Motion &mot_;
	Target &tar_;
	//Rendering &ren_;
};

//********************************* INITIALIZATION *********************************

class Actors : public Props{
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

//************************************************** DRAW *************************************************** 

	void Actors ::	refresh (ID id);
	virtual void Actors ::	draw (ID id);	

	Actor Actors::getActor(ID id);
//************************************************** MEMBERS ***************************************************
	
	vector<Target> target;
	vector<Motion> motion;
	vector<Obstacles> obstacles;

	float delta;
	ID count;

	static MotionState walking;
	static AttackState charge;

};
#endif