#ifndef COLLISIONSET_H
#define COLLISIONSET_H

#include "GridData.h"
//********************************* CONSTANTS *********************************
struct CollisionData {
	ID obj1;
	ID obj2;
	float dist;
	glm::vec3 distV;
};



//********************************* INITIALIZATION *********************************

class CollisionSet {
	public: 

	CollisionSet::CollisionSet();
	
	void CollisionSet::clear();
	ID CollisionSet::size(){return set.size();}

	void CollisionSet::add(ID g1, ID g2, float d,  glm::vec3 dv);

	CollisionData CollisionSet::getCollisionData(ID i);

	vector <CollisionData> set;

	//CollisionResponse 
	//CollisionCriteria

};
#endif