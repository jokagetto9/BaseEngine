#ifndef OBSTACLES_H
#define OBSTACLES_H

#include "Motion.h"


//********************************* CONSTANTS *********************************
struct Ob {
	glm::vec3 pos;
	ID sizeP;
	float d;
	//size scale
};
struct SizeProfile{
	float crashRad;
	float sepRad;
	float sepWt;
	float cohRad;
	float cohWt;
};

const float GROUP_RANGE = 50.0f ; // m
const float GROUP_RANGE_SQ = GROUP_RANGE*GROUP_RANGE ; // m

const float COHESION_WEIGHT   = 0;//0.2f;
const float ALIGNMENT_WEIGHT  = 0;//0.3f;
const float SEPARATION_WEIGHT = 1;//0.5f;
const float SEPARATION_R = 2.0f;

const float FURTHEST = 100000;
//********************************* INITIALIZATION *********************************


class Obstacles: public Component  {
public:
	Obstacles::Obstacles();
	Obstacles::Obstacles(ID max);
	void Obstacles::clear();
	
	void Obstacles::testObject(glm::vec3 pos, Ob &o);
	void Obstacles::addObject(ID i, Ob &o);
	void Obstacles::shuffle(ID i1, ID i2);
	void Obstacles::updateObDist(glm::vec3 pos);

	void Obstacles::applyProfile(ID id);
	glm::vec3 Obstacles::calcAlign();
	glm::vec3 Obstacles::calcSep(glm::vec3 pos);
	glm::vec3 Obstacles::calcCoh(glm::vec3 pos);


	bool Obstacles::collide(glm::vec3 pos);	
	void Obstacles::swap(ID i1, ID i2);

	vector <glm::vec3> ob;
	vector <float> obDist;
	vector <ID> obSize;
	float furthest;
	ID count;
	XZI grid;

	static SizeProfile ignore;
	static SizeProfile & sizeP;
	static vector<SizeProfile> sizeProfiles;

};


#endif