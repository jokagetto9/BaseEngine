#ifndef PARTICLES_H
#define PARTICLES_H

#include "Props.h"
#include "../Components/Motion.h"
#include "../Components/Obstacles.h"
#include "../Components/Target.h"
//********************************* CONSTANTS *********************************


//********************************* INITIALIZATION *********************************

class Particles : public Props {
	public: 
		Particles::		Particles(){dict = &particleList;}
		ID Particles ::	createParticle (ParticleList& list, EntityXZ ent);
		 
	void Particles ::	update (float physDelta);
	void Particles ::	update (ID id);
	void Particles::chargeParticle (ID id, glm::vec3 targ);
//************************************************** DRAW *************************************************** 
	
	virtual void Particles::reserve(ID max);
	void Particles ::	refresh (ID id);
	bool Particles:: add(ID id, Rendering& r, Location& l, Motion &m, Animation &a);
	virtual bool Particles ::canMove (){return true;}

//************************************************** MEMBERS ***************************************************
	 
	vector<Motion> motion;
	vector<Obstacles> obstacles;
	vector<Target> target;
	float delta;
	
	static AttackState charge;
};
#endif