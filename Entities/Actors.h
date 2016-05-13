#ifndef ACTORS_H
#define ACTORS_H

#include "Props.h"
#include "Components\AI.h"
#include "Components\Physics.h"
//********************************* CONSTANTS *********************************


//********************************* INITIALIZATION *********************************

class Actors : public Props{
	public: 
	Actors::		Actors();
	Actors ::	Actors (ID reserve);

	vector<AI> ai;
	vector<Physics> physics;

};
#endif