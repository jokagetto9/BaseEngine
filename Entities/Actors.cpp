#include "Actors.h"

MotionState  Actors::moving;



void Actors::reserve(ID max){
	if (max < MAX_COMPONENTS){
		Particles::reserve(max);
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

bool Actors:: createActor(ID id, Rendering& r, Location& l, Motion &m, Animation &a){
	ID i = nextFree();
	if (i < MAX_COMPONENTS){
		type[i] = id;
		rendering[i] = r;
		location[i] = l;
		motion[i] = m;
		animation[i] = a;
		state[i] = &still;
		gData[i] = GridData(i, 3);
		count++;
		return true;
	}
	return false;
}


void Actors::setTarget(ID id, glm::vec3 pos){
	if (id < count)
		target[id].setTarget(pos);
}

void Actors::activateAll(glm::vec3 pos){
	for (ID i = 0; i < count; i++){
		target[i].setTarget(pos);
	}
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
		glm::vec3 tempV = scaleVector(location[id].pos(), target[id].targetP, 10);
		motion[id].setTarget(tempV);
		state[id] = &charge;
	}else{
		state[id] = &still;
	}
}


//********************************* MEMBER FUNCTIONS *********************************

Actor Actors::getActor(ID id){
	Actor a = {state[id], location[id], motion[id], target[id]};
	return a;
}