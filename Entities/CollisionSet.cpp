#include "CollisionSet.h"

void CollisionSet::add(GridData* g1, GridData* g2){
	obj1.push_back(g1);
	obj2.push_back(g2);
}