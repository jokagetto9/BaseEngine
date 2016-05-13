#ifndef PHYSICS_H
#define PHYSICS_H

#include "Component.h"


//********************************* CONSTANTS *********************************

const float TURBO_SPEED = 0.2f;  // m/ms
const float TURBO_ACCEL = 0.0005f;  // m/ms^2
const float WALK_MAX_SPEED = 0.01f;  // m/ms
const float RUN_MAX_SPEED = 0.0125f;//0.00625f;  // m/ms
const float RUN_MAX_ACCEL = RUN_MAX_SPEED;//0.00625f;  // m/ms^2
//********************************* INITIALIZATION *********************************


class Physics: public Compoment  {
public:
	
	Physics::Physics();


		glm::vec3 speed, prevPos;	
		float prevTheta;
		//float targetSpeed;
};


#endif