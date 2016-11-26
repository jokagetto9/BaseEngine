#include "CollisionSet.h"

CollisionSet::CollisionSet(){
	max = 10;
	set.reserve(max);

}

void CollisionSet::clear(){
	set.clear();
}


void CollisionSet::add(ID g1, ID g2, float d, glm::vec3 dv){
	//if( set.size() < max){
		CollisionData data = {g1, g2, d, dv};
		set.push_back(data);
	//}
}



CollisionData CollisionSet::getCollisionData(ID i){
	return set[i];
}
