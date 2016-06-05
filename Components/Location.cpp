//********************************* INITIALIZATION *********************************
#include "Location.h"

Location::Location(){		
	x_ = 0; 	z_ = 0;		y_ = 0;
	//scale = 1; 
	//dir = DUNNO;
	theta = 0;
}


void Location::adjustPos(Drctn d, float dist){	
	x_ += ADJ_[d].x * dist;	
	z_ += ADJ_[d].z * dist; 
}


bool Location::withinRange(glm::vec3 tPos, float range){
	float distSQ = getDistSq(tPos, pos());
	//range += NULL_R;
	if (distSQ <= range*range){
		return true;
	}else{
		return false;}
}
//
