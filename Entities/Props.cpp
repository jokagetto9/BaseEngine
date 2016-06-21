#include "Props.h"

State  Props ::off;
StillState  Props ::still;

void Props ::	reserve (ID max){
	if (max < MAX_COMPONENTS){
		type.resize(max);
		rendering.resize(max);
		location.resize(max);
		state.resize(max);
		clear();
	} 
}



bool Props:: add(ID id, Rendering& r, Location& l){
	ID i = nextFree(); 
	if (i < MAX_COMPONENTS){
		type[i] = id;
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
	count = 0;
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



void Props ::	draw (ID id){
	int index = rendering[id].texIndex; 
	location[id].translate();	
		if (index < 0){
			index += 16;
			M->gridBO.flip(-1, 1);
		}
		ID start = 0;
		if (animation.size() > id)
			start = animation[id].start;
		M->gridBO.drawGrid(start + index);	
	glPopMatrix(); //}	
}




ID Props::getSizeIndex(ID id){
	if (dict){
		ID i = type[id];
		return dict->getSizeIndex(i);
	}else
		return 0;
}
