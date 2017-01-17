#ifndef AIBRAIN_H
#define AIBRAIN_H

#include "Component.h"
#include "../Template/Functions.h"


//********************************* CONSTANTS *********************************

//********************************* INITIALIZATION *********************************


class AIBrain {
public:
	AIBrain::AIBrain(){}

	vector <AIV> vectors;
	vector <AIVBehaviour *> movement;
	

};

#endif