//********************************* INITIALIZATION *********************************
#include "AI.h"

AI::AI(){		
	targetP = glm::vec3(0.0); 
}

void AI::	setTarget(const glm::vec3 pos){
	targetP = pos;
}


glm::vec3 AI::getTarget(glm::vec3 pos, float aiDelta){
	glm::vec3 targetV = targetP - pos;	
	float maxChange = MIN_ACCEL * aiDelta;
	truncate (targetV, maxChange);
	return targetV;
}

/*/
void AI:: crash (){
	float d = getDistSQ(targetP);
	if (d < 3*3){
		dead = true;
	}
}//*/