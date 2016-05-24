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

	float camTheta = C->getCameraTheta(t.pos(), false);	
	camTheta -= t.theta;
	r.texIndex = a.getThetaIndex(facing(camTheta));
	if (!state[id]->still()) 
		r.texIndex += a.frameTick(delta);
}


void Actors ::	draw (ID id){
	translation[id].translate();	
		M->gridBO.drawx16(rendering[id].texIndex);	
	glPopMatrix(); //}	
}


//********************************* MEMBER FUNCTIONS *********************************

Actor Actors::getActor(ID id){
	Actor a = {state[id], translation[id], motion[id], ai[id]};
	return a;
}