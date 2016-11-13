#include "Particles.h"


AttackState  Particles::charge;

void Particles::reserve(ID max){
	if (max < MAX_COMPONENTS){
		animation.resize(max);
		motion.resize(max);
		obstacles.resize(max);
		target.resize(max);
		Props::reserve(max);
	}
}


ID Particles ::	createParticle (ParticleList& list, EntityXZ ent){
	ID i = nextFree(); 
	if (i < MAX_COMPONENTS){
		Rendering r;		Location l;
		type[i] = ent.id;

		location[i].place(ent.x, ent.z);
		rendering[i].tex = list.getProfile(ent.id).tex;
		animation[i] = particleList.anim[ent.id];
		motion[i] = Motion(particleList.max[ent.id]);
		gData[i] = GridData(i, 2);
		health[i].set(12);
		health[i].setRate(-1);
		state[i] = &charge;
		count++;
		return i;
	}
	return MAX_COMPONENTS;
}


//************************************************** UPDATE ***************************************************

void Particles ::	update (float physDelta){	
	delta = physDelta;
	ID s = state.size();
	for (ID i = 0; i < s; i++){
		update(i);
	}
}

void Particles ::	update (ID id){
	motion[id].updateSpeed(delta);
	if (!state[id]->still()){
		//TODO if stopped change to still
		motion[id].move(location[id]);		
		
	}
	if(gData[id].enabled)
		updateGrid(id);
	//TODO world wrap	
	//NEWBRANCH quadtree
}

void Particles::chargeParticle (ID id, glm::vec3 targ){
	if (id < count){
		glm::vec3 tempV = scaleVector(location[id].pos(), targ, 10);
		motion[id].setTarget(tempV);
		state[id] = &charge;
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
		gData[i] = GridData(i, 2);
		count++;
		return true;
	}
	return false;
}