#ifndef ACTORS_H
#define ACTORS_H

#include "Props.h"
#include "Components\AI.h"
#include "Components\Motion.h"
//********************************* CONSTANTS *********************************


//********************************* INITIALIZATION *********************************

class Actors : public Props{
	public: 
	Actors::	Actors(){}
	void Actors::reserve(ID max);
	void Actors::reset();
	void Actors::reset(ID id);


	void Actors ::	draw (float delta);

	vector<AI> ai;
	vector<Motion> motion;


	static MotionState walking;

};
#endif