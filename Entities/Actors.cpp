#include "Actors.h"

MotionState  Actors::walking;
AttackState  Actors::charge;



void Actors::reserve(ID max){
	if (max < MAX_COMPONENTS){
		animation.resize(max);
		ai.resize(max);
		motion.resize(max);
		Props::reserve(max);
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
	ai[id] = AI();
	motion[id] = Motion();
	animation[id] = Animation();
}

bool Actors:: add(Rendering& r, Translation& t, Motion &m, Animation &a){
	ID i = nextFree();
	if (i < MAX_COMPONENTS){
		rendering[i] = r;
		translation[i] = t;
		motion[i] = m;
		animation[i] = a;
		state[i] = &still;
		return true;
	}
	return false;
}


void Actors::activate(ID id, glm::vec3 pos){
	ID s = state.size();
	for (ID i = 0; i < s && i < id; i++){
		ai[i].setTarget(pos);
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
		motion[id].move(translation[id]);



		
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
	if (notZero(ai[id].targetP)){
		glm::vec3 tempV = translation[id].pos();
		tempV = ai[id].getTarget(tempV, delta);
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
	Translation &t = translation[id]; 
	
	ID tweak = 0;
	if (!state[id]->still()) 
		tweak = a.frameTick(delta);


	float camTheta = C->getCameraTheta(t.pos(), false);	
	camTheta -= t.theta;
	tweak += a.getThetaIndex(camTheta);
	rendering[id].texIndex = tweak;
}


void Actors ::	draw (ID id){
	int index = rendering[id].texIndex; 
	translation[id].translate();	
		if (index < 0){
			index += 16;
		}
		M->gridBO.drawx16(animation[id].start + index);	
	glPopMatrix(); //}	
}


//********************************* MEMBER FUNCTIONS *********************************

Actor Actors::getActor(ID id){
	Actor a = {state[id], translation[id], motion[id], ai[id]};
	return a;
}