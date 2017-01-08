#ifndef TARGETSYSTEM_H
#define TARGETSYSTEM_H

#include "EntityList.h"
//********************************* CONSTANTS *********************************

//********************************* INITIALIZATION *********************************

class TargetSystem {
public:
	
static void TargetSystem::setTarget(Target &t, glm::vec3 pos);

static void TargetSystem::chargeParticle (glm::vec3 pos, glm::vec3 targ, Motion& m, State* s);

};
#endif