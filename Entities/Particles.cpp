#include "Particles.h"


AttackState  Particles::charge;

void Particles::reserve(ID max){
	if (max < MAX_COMPONENTS){
		animation.resize(max);
		motion.resize(max);
		obstacles.resize(max);
		Props::reserve(max);
	}
}

//************************************************** DRAW *************************************************** 


void Particles ::	refresh (ID id){
	Rendering &r = rendering[id]; 
	Animation &a = animation[id]; 
	Location &t = location[id]; 
	
	int tweak = 0;
	if (!state[id]->still()) 
		tweak = a.frameTick(delta);


	float camTheta = C->getCameraTheta(t.pos(), false);	
	camTheta -= t.theta;
	tweak += a.getThetaIndex(camTheta);
	rendering[id].texIndex = tweak;
}





bool Particles:: add(ID id, Rendering& r, Location& l, Motion &m, Animation &a){
	ID i = nextFree();
	if (i < MAX_COMPONENTS){
		type[i] = id;
		rendering[i] = r;
		location[i] = l;
		motion[i] = m;
		animation[i] = a;
		state[i] = &charge;
		count++;
		return true;
	}
	return false;
}