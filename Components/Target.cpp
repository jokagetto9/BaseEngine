//********************************* INITIALIZATION *********************************
#include "Target.h"

Target::Target(){		
	targetP = glm::vec3(0.0); 
}

void Target::	setTarget(const glm::vec3 pos){
	targetP = pos;
}


glm::vec3 Target::getTarget(glm::vec3 pos, float aiDelta){
	return scaleVector(pos, targetP, 10);
}

/*/
void Target:: crash (){
	float d = getDistSQ(targetP);
	if (d < 3*3){
		dead = true;
	}
}//*/



