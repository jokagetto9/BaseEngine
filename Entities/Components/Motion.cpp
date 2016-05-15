//********************************* INITIALIZATION *********************************
#include "Motion.h"

Motion::Motion(){		
	speed = glm::vec3(0.0); 
	prevPos = glm::vec3(0.0);	
	maxS = RUN_MAX_ACCEL;
}


void Motion::backTrack(Translation& t){
	t.x_ = prevPos.x;
	t.y_ = prevPos.y;
	t.z_ = prevPos.z;
	speed = glm::vec3(0.0);
}


void Motion::move(Translation& t){
	setPrev(t.pos());	// track last position for collision detection
	t.push(speed.x, speed.z);	//move according to speed for physDelta ms
	t.theta = findTheta(speed);
}


void Motion::move(Oriet o){
	float tempTheta = C->theta + D_ROTATE[o];	
	targetV = calcThetaV(tempTheta);
}



void Motion::updateSpeed(float physDelta){
	if (notZero(targetV)){
		float maxChange = maxS * physDelta;
		//float maxChange = RUN_MAX_ACCEL * physDelta;		
		
		truncate (targetV, maxChange);	 //forceDiagonal

		setSpeed(targetV);
		//speed += targetV;		
		//truncate(speed,  maxS);						// scale change to max speed
		//halting = false;

	} else 
		stop();
		//dec = speed;
		//truncate (dec, maxChange/2);				//scale motion to accel rate
		//speed -= dec;
		//if (notZero(dec))
			//halting = true;

}

/*/
void Motion::forceDiagonal(float physDelta){
		if (false){//targetV.x != 0 && targetV.z != 0){	
			if (targetV.x > 0)	targetV.x = 1;
			else				targetV.x = -1;
			if (targetV.z > 0)	targetV.z = 1;
			else				targetV.z = -1;
			targetV *= maxChange; 
		}else 
			truncate (targetV, maxChange);
}
//*/