#ifndef AI_H
#define AI_H

#include "Motion.h"


//********************************* CONSTANTS *********************************

//********************************* INITIALIZATION *********************************


class AI: public Component  {
public:
	
	AI::AI();
	
	void AI::	setTarget(const glm::vec3 pos);
	glm::vec3 AI::getTarget(glm::vec3 pos,float aiDelta);

	
	void AI::noTarget(){targetP = glm::vec3(0.0);}

	void AI:: crash ();

	glm::vec3 targetP;
	
};


#endif