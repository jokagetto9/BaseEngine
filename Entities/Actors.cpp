#include "Actors.h"

MotionState  Actors::walking;

void Actors::reserve(ID max){
	if (max < MAX_COMPONENTS){
		rendering.resize(max);
		translation.resize(max);
		animation.resize(max);
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
	animation[id] = Animation();
}



void Actors ::	draw (float delta){
	ID s = state.size();
	for (ID i = 0; i < s; i++){
		if (state[i]->on()){
			Rendering &r = rendering[i]; 
			Animation &a = animation[i]; 
			Translation &t = translation[i]; 


			float camTheta = C->getCameraTheta(t.pos(), false);	
			camTheta -= t.theta;
			r.texIndex = a.getThetaIndex(t.facing());
			if (!state[i]->still()) 
				r.texIndex += a.frameTick(delta);


			t.translate();		
				if (r.texIndex >= 0 && r.texIndex < 16) 
					M->gridBO.drawx16(r.texIndex);	
			glPopMatrix(); //}	
		}
	}

}