#ifndef MOTION_H
#define MOTION_H

#include "Location.h"


//********************************* CONSTANTS *********************************

const float PHYS_DELTA = 1000/20;	// ms per update
const float TURBO_SPEED = 0.2f;  // m/ms
const float TURBO_ACCEL = 0.0005f;  // m/ms^2
const float WALK_MAX_SPEED = 0.01f;  // m/ms
const float MIN_SPEED = 0.125/PHYS_DELTA;//0.00625f;  // m/ms
const float MIN_ACCEL = 0.025/PHYS_DELTA;//0.00625f;  // m/ms^2

struct MotionMax {
	float accel, speed;
};


//********************************* INITIALIZATION *********************************


class Motion: public Component  {
public:
	
	Motion::Motion();
	Motion::Motion(MotionMax& mm);
	
	void Motion::backTrack(Location& l);
	void Motion::move(Location& l);
	
	void Motion::stop(){speed = glm::vec3(0.0);}
	
	void Motion::setSpeed(glm::vec3 pos){speed = pos;}
	void Motion::setTarget(glm::vec3 v){targetV = v;}
	void Motion::setPrev(glm::vec3 pos){prevPos = pos;}
	
	void Motion::move(Oriet o);	
	void Motion::halt(){targetV = glm::vec3(0.0);}
	
	void Motion::updateSpeed(float physDelta);
	
	void Motion::adjust(glm::vec3 v, float aiDelta);

		glm::vec3 speed, targetV, prevPos;	
		float prevTheta;
		MotionMax max;

		//float targetSpeed;
};


#endif