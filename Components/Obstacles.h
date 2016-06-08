#ifndef OBSTACLES_H
#define OBSTACLES_H

#include "Motion.h"


//********************************* CONSTANTS *********************************

const float GROUP_RANGE = 50.0f ; // m
const float GROUP_RANGE_SQ = GROUP_RANGE*GROUP_RANGE ; // m
const int GROUP_MIN = 30; //min school spawneration

const float COHESION_WEIGHT   = 0;//0.2f;
const float ALIGNMENT_WEIGHT  = 0;//0.3f;
const float SEPARATION_WEIGHT = 1;//0.5f;
const float SEPARATION_R = 2.0f;

const float EAT_RATIO = 0.8;
const float MAX_SCALE = 3.5;

const float CATCH_RANGE_SQ = 400.0f; //m squared

const float FURTHEST = 100000;
//********************************* INITIALIZATION *********************************


class Obstacles: public Component  {
public:
	Obstacles::Obstacles();
	Obstacles::Obstacles(ID max);
	void Obstacles::clear();
	
	void Obstacles::testObject(glm::vec3 pos, float d);
	void Obstacles::addObject(ID i, glm::vec3 pos, float d);
	void Obstacles::shuffle(ID i1, ID i2);
	void Obstacles::updateObDist(glm::vec3 pos);

	glm::vec3 Obstacles::calcAlign();
	glm::vec3 Obstacles::calcSep(glm::vec3 pos);
	glm::vec3 Obstacles::calcCoh(glm::vec3 pos);
	bool Obstacles::collide(glm::vec3 pos);

	
	void Obstacles::swap(ID i1, ID i2);


	vector <glm::vec3> ob;
	vector <float> obDist;
	float furthest;
	ID count;

};


#endif