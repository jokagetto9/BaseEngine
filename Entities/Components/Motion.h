#ifndef MOTION_H
#define MOTION_H

#include "Translation.h"


//********************************* CONSTANTS *********************************

const float TURBO_SPEED = 0.2f;  // m/ms
const float TURBO_ACCEL = 0.0005f;  // m/ms^2
const float WALK_MAX_SPEED = 0.01f;  // m/ms
const float RUN_MAX_SPEED = 0.0125f;//0.00625f;  // m/ms
const float RUN_MAX_ACCEL = RUN_MAX_SPEED;//0.00625f;  // m/ms^2


Oriet facing(float theta);

//********************************* INITIALIZATION *********************************


class Motion: public Component  {
public:
	
	Motion::Motion();
	
	void Motion::backTrack(Translation& t);
	void Motion::move(Translation& t);
	
	void Motion::stop(){speed = glm::vec3(0.0);}
	
	void Motion::setSpeed(glm::vec3 pos){speed = pos;}
	void Motion::setTarget(glm::vec3 v){targetV = v;}
	void Motion::setPrev(glm::vec3 pos){prevPos = pos;}
	
	void Motion::move(Oriet o);	
	void Motion::halt(){targetV = glm::vec3(0.0);}
	
	void Motion::updateSpeed(float physDelta);

		glm::vec3 speed, targetV, prevPos;	
		float prevTheta, maxS;

		//float targetSpeed;
};


#endif