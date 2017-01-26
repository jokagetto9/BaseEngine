#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include "../Components/Motion.h"
#include "../Components/Size.h"

struct AIV{
	float rat;
	float rad;
	glm::vec3 v;
};

class AIBehaviour {
public:
	//virtual glm::vec3 calc(ID eIndex, glm::vec3 v) {return glm::vec3(0);};
	virtual void apply(ID eIndex) {};
};

class AIVBehaviour {
public:

	virtual glm::vec3 calc(ID eIndex, glm::vec3 v) {return glm::vec3(0);}
	virtual void apply(ID eIndex, AIV &aiv) {}
};

#endif