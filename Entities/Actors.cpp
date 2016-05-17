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
	int shaderProfiles = 10;
	batchDraw.resize(shaderProfiles);
	for (ID i = 0; i < shaderProfiles; i++){
		batchDraw[i].reserve(20);
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
	ID s = state.size();
	for (ID i = 0; i < s; i++){
		update(i, physDelta);
	}
}

void Actors ::	update (ID id, float physDelta){
	motion[id].updateSpeed(physDelta);
	if (!state[id]->still()){
		//TODO if stopped change to still
		motion[id].move(translation[id]);



		
	}//TODO world wrap	
	//NEWBRANCH quadtree
}

void Actors ::	aiUpdate (float aiDelta){
	ID s = state.size();
	for (ID i = 0; i < s; i++){
		if (state[i]->on()){
			aiUpdate(i, aiDelta);
		}
	}
}

void Actors ::	aiUpdate (ID id, float aiDelta){
	//TODO if has target
	if (notZero(ai[id].targetP)){
		glm::vec3 tempV = translation[id].pos();
		tempV = ai[id].getTarget(tempV, aiDelta);
		motion[id].setTarget(tempV);
		state[id] = &charge;
	}else{
		state[id] = &still;
	}
}

//************************************************** DRAW *************************************************** 

void Actors ::	refresh(float delta){
	batchDraw[0].clear();
	ID s = state.size();
	for (ID i = 0; i < s; i++){
		if (state[i]->on()){
			refresh(i, delta);
		}
	}

}

void Actors ::	refresh (ID id, float delta){
	Rendering &r = rendering[id]; 
	Animation &a = animation[id]; 
	Translation &t = translation[id]; 

	float camTheta = C->getCameraTheta(t.pos(), false);	
	camTheta -= t.theta;
	r.texIndex = a.getThetaIndex(facing(camTheta));
	if (!state[id]->still()) 
		r.texIndex += a.frameTick(delta);
	//TODO add shader profile
	batchDraw[0].push_back(id);


}


void Actors ::	draw (){
	int shaderProfiles = batchDraw.size();	
	for (ID profile = 0; profile < shaderProfiles; profile++){
		if (profile == 0)
			M->gridBO.prepNPC(); //prep
		int s = batchDraw[profile].size();	
		for (ID i = 0; i < s; i++){
			draw(batchDraw[profile][i]);
		}
	}
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