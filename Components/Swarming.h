#ifndef SWARMING_H
#define SWARMING_H

#include "Location.h"
//********************************* CONSTANTS *********************************
struct SwarmVector {
	glm::vec3 v;
	float rad;
	float rat;
};

//********************************* INITIALIZATION *********************************

class Swarming {
	public: 

		Swarming::Swarming();
		
	void Swarming::reset();
	


	void Swarming::calcSep(float rad, float d, glm::vec3 dv);
			
	
	void Swarming::normalizeVectors();
	


		SwarmVector col, sep, avo, ali, coh;



};
#endif