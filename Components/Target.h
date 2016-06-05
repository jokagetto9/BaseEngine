#ifndef TARGET_H
#define TARGET_H

#include "Motion.h"


//********************************* CONSTANTS *********************************


//********************************* INITIALIZATION *********************************


class Target: public Component  {
public:
	
	Target::Target();
	
	void Target::	setTarget(const glm::vec3 pos);
	glm::vec3 Target::getTarget(glm::vec3 pos,float aiDelta);

	
	void Target::noTarget(){targetP = glm::vec3(0.0);}

	void Target:: crash ();

	glm::vec3 targetP;
	
};


#endif