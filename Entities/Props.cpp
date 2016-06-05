#include "Props.h"

State  Props ::off;
StillState  Props ::still;

void Props ::	reserve (ID max){
	if (max < MAX_COMPONENTS){
		rendering.resize(max);
		location.resize(max);
		size.resize(max);
		state.resize(max);
		clear();
	}
}



bool Props:: add(Rendering& r, Location& l){
	ID i = nextFree();
	if (i < MAX_COMPONENTS){
		rendering[i] = r;
		location[i] = l;
		state[i] = &still;
		return true;
	}
	return false;
}


ID Props:: nextFree(){
	ID s = state.size();
	for (ID i = 0; i < s; i++){
		if (!state[i]->on())
			return i;
	}
	return MAX_COMPONENTS;
}



void Props::clear(){
	ID s = state.size();
	for (ID i = 0; i < s; i++){
			state[i] = &off;
	}
}

void Props::reset(){
	clear();
	ID s = state.size();
	for (ID i = 0; i < s; i++){
		reset(i);
	}
}

void Props::reset(ID id){	
	//rendering[id] = Rendering(PROP, 0, 0);
	location[id] = Location();
}
