#ifndef ACTORS_H
#define ACTORS_H

#include "Props.h"
#include "Components/AI.h"
#include "Components/Motion.h"
#include "../../Display/ModelManager.h"
//********************************* CONSTANTS *********************************


//********************************* INITIALIZATION *********************************

class Actors : public Props{
	public: 
	Actors::	Actors(){}
	void Actors::reserve(ID max);
	void Actors::reset();
	void Actors::reset(ID id);
	

//************************************************** UPDATE ***************************************************
	void Actors ::	update (float physDelta);
	void Actors ::	update (ID id, float physDelta);

	void Actors ::	aiUpdate (float aiDelta);
	void Actors ::	aiUpdate (ID id, float aiDelta);

//************************************************** DRAW *************************************************** 
	void Actors ::	refresh (float delta);
	void Actors ::	refresh (ID id, float delta);
	virtual void Actors ::	draw ();
	virtual void Actors ::	draw (ID id);

	
//************************************************** MEMBERS ***************************************************

	vector<AI> ai;
	vector<Motion> motion;

	vector<vector <ID>> batchDraw;
	vector<ID> shaderprofile;

	static MotionState walking;

};
#endif