//********************************* INITIALIZATION *********************************
#include "Motion.h"


Motion::Motion(){		
	speed = glm::vec3(0.0); 
	prevPos = glm::vec3(0.0);	
	max.accel = MIN_ACCEL * 20;
	max.speed = MIN_SPEED * 4;
}

Motion::Motion(MotionMax& mm){		
	speed = glm::vec3(0.0); 
	prevPos = glm::vec3(0.0);	
	max.accel = MIN_ACCEL * mm.accel;
	max.speed = MIN_SPEED * mm.speed;
}


void Motion::backTrack(Location& l, float ratio){
	glm::vec3 pos = l.pos();
	l.place(prevPos);
	pos -= prevPos;
	pos *= ratio;
	l.push(pos.x, pos.z);
	//l.x_ = .x; 
	//l.y_ = prevPos.y;
	//l.z_ = prevPos.z;
	//speed /= 2;
	speed = glm::vec3(0.0);
} 

void Motion::move(Location& l){
	setPrev(l.pos());	// track last position for collision detection
	l.push(speed.x, speed.z);	//move according to speed for physDelta ms
	l.theta = findTheta(speed);
}


void Motion::move(Oriet o){
	float tempTheta = C->theta + D_ROTATE[o];	
	targetV = calcThetaV(tempTheta);
}



void Motion::updateSpeed(float physDelta){
	if (notZero(targetV)){
		float maxChange = max.accel * physDelta;		
		truncate (targetV, maxChange);	 //forceDiagonal

		speed += targetV;	
		truncate(speed,  max.speed*physDelta);						// scale change to max speed
		//halting = false;

	} else 
		stop();
		//dec = speed;
		//truncate (dec, maxChange/2);				//scale motion to accel rate
		//speed -= dec;
		//if (notZero(dec))
			//halting = true;

}


void Motion::adjust(glm::vec3 v, float aiDelta){
	targetV += v;
	float maxChange = MIN_ACCEL * aiDelta;
	truncate (targetV, maxChange);
}


/*/
void Motion::fastDiagonal(float physDelta){
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




glm::vec3 scaleVector(glm::vec3 p1, glm::vec3 p2, float scale){
	glm::vec3 targetV = p2 - p1;	
	truncate (targetV, 10);
	return targetV;
}