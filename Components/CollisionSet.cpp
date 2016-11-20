#include "CollisionSet.h"

CollisionSet::CollisionSet(){
	set.reserve(10);

}

void CollisionSet::clear(){
	set.clear();
}


void CollisionSet::add(ID g1, ID g2, float d, glm::vec3 dv){
	CollisionData data = {g1, g2, d, dv};
	set.push_back(data);
}



CollisionData CollisionSet::getCollisionData(ID i){
	return set[i];
}
