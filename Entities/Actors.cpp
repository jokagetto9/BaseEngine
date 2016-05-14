#include "Actors.h"

MotionState  Actors::walking;

void Actors::reserve(ID max){
	if (max < MAX_COMPONENTS){
		rendering.resize(max);
		translation.resize(max);
		ai.resize(max);
		motion.resize(max);
		state.resize(max);
		clear();
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
}

void Actors ::	draw (float delta){
	ID s = state.size();
	for (ID i = 0; i < s; i++){
		if (state[i]->on()){
			Rendering *r = &rendering[i]; 
			Translation *t = &translation[i]; 
			float camTheta;
			camTheta =  C->getCameraTheta(t->pos(), false);	
			camTheta -= t->theta;
	
			t->translate();
				r->walkAnim.draw(camTheta, delta);
			glPopMatrix(); //}	
		}
	}

}