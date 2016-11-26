#include "Swarming.h"


//get distance
//compare against list of radii and boxes
//sort by priority schema (distance) 
//make limited list of collisions
//sum collisions into response behaviours

//	float baseRad;
//	float crashRad;
//	float sepRad;
//	float sepWt;
//	float cohRad;
//	float cohWt;
//

//	sp = buildSizeProfile(0, 0.2, 2, 9, 10, 0.001); //gnome

Swarming::Swarming(){
	reset();
	
	
	col.rad = 1.2;
	col.rat = 1;

	sep.rad = 2;
	sep.rat = 10;
	
	coh.rad = 8;
}

void Swarming::reset(){
	sep.v = glm::vec3(0.0);

}





void Swarming::calcSep(float rad, float d, glm::vec3 dv){
	//dv *= d/(d+col.rad); 
	if (d <= rad){
		float c = (rad - d)/ rad;
		sep.v += c * dv/d;
	}
}

void Swarming::normalizeVectors(){
	truncate(sep.v, sep.rat);
}
