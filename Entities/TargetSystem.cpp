#include "TargetSystem.h"

void TargetSystem::setTarget(Target &t, glm::vec3 pos){
		t.setTarget(pos);
}


void TargetSystem::scaleMotion (glm::vec3 pos, glm::vec3 targ, Motion& m, State* s){

	glm::vec3 tempV = scaleVector(pos, targ, 10);
	m.setTarget(tempV);
	s = &EntityList::charge;
}
