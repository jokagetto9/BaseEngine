#include "Actors.h"

MotionState  Actors::walking;
AttackState  Actors::charge;



void Actors::reserve(ID max){
	if (max < MAX_COMPONENTS){
		animation.resize(max);
		target.resize(max);
		motion.resize(max);
		obstacles.resize(max);
		Props::reserve(max);
		count = 0;
	}
}


void Actors::reset(){
	clear();
	ID s = state.size();
	for (ID i = 0; i < s; i++){
		//Props::reset(i);
		reset(i);
	}
}

void Actors::reset(ID id){	
	target[id] = Target();
	motion[id] = Motion();
	animation[id] = Animation();
	obstacles[id].clear();
}

bool Actors:: add(Rendering& r, Location& l, Motion &m, Animation &a){
	ID i = nextFree();
	if (i < MAX_COMPONENTS){
		rendering[i] = r;
		location[i] = l;
		motion[i] = m;
		animation[i] = a;
		state[i] = &still;
		count++;
		return true;
	}
	return false;
}


void Actors::activate(ID id, glm::vec3 pos){
	ID s = state.size();
	for (ID i = 0; i < s && i < id; i++){
		target[i].setTarget(pos);
	}
}

void Actors::activateAll(glm::vec3 pos){
	for (ID i = 0; i < count; i++){
		target[i].setTarget(pos);
	}
}

//************************************************** UPDATE ***************************************************

void Actors ::	update (float physDelta){	
	delta = physDelta;
	ID s = state.size();
	for (ID i = 0; i < s; i++){
		update(i);
	}
}

void Actors ::	update (ID id){
	motion[id].updateSpeed(delta);
	if (!state[id]->still()){
		//TODO if stopped change to still
		motion[id].move(location[id]);		
	}//TODO world wrap	
	//NEWBRANCH quadtree
}

void Actors ::	aiUpdate (float aiDelta){
	delta = aiDelta;
	ID s = state.size();
	for (ID i = 0; i < s; i++){
		if (state[i]->on()){
			aiUpdate(i);
		}
	}
}
	
void Actors ::	aiUpdate (ID id){
	//TODO if has target
	if (notZero(target[id].targetP)){
		glm::vec3 tempV = location[id].pos();
		tempV = target[id].getTarget(tempV, delta);
		motion[id].setTarget(tempV);
		state[id] = &charge;
	}else{
		state[id] = &still;
	}
}

//************************************************** DRAW *************************************************** 


void Actors ::	refresh (ID id){
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


void Actors ::	draw (ID id){
	int index = rendering[id].texIndex; 
	location[id].translate();	
		if (index < 0){
			index += 16;
			M->gridBO.flip(-1, 1);
		}
		M->gridBO.drawx16(animation[id].start + index);	
	glPopMatrix(); //}	
}


//********************************* MEMBER FUNCTIONS *********************************

Actor Actors::getActor(ID id){
	Actor a = {state[id], location[id], motion[id], target[id]};
	return a;
}