//********************************* INITIALIZATION *********************************
#include "Animation.h"

Animation::Animation(){
	type = WALK12;
	start = 0; end = 0;
	tpf = 100 + rand() % 16;
	tick = rand() % tpf;
}


void Animation::setCyclic(ID min, ID max, ID frames){
	type = CYCLIC;
	//if (tpf > 0) tick = rand() % tpf;
	
	tpf = (max - min)*frames;	
	tick = rand() % tpf;

	//tick = 0;	
	start = min;	
	end = max;
	
}

//********************************* DRAW *********************************


// cycle looping animations
int Animation::frameTick( float frameDelta){
	if (type == WALK8){
		tick += 0.2 * frameDelta;
		if (tick >= tpf )tick -= tpf;
		if (tick >= tpf/2)	{ glTranslatef(0, 0.5, 0);   return 1;	}
		else if (tick >= tpf*3/4 && tick < tpf)	return 1;
	}
	else if (type == WALK12){
		tick += 0.1 * frameDelta;
		if (tick >= tpf )tick -= tpf;
		if (tick >= tpf/4 && tick < tpf/2)	return - 1;	
		else if (tick >= tpf*3/4 && tick < tpf)	return 1;
	}	
	else if (type == CYCLIC){
		tick += 0.1 * frameDelta;
		if (tick >= tpf )tick -= tpf;
		int i = tick/(tpf/end);
		//int i = (int)tick % index; 
		if (i < end)
			return i;
		else 
			return 0;
	}
	return 0;
}
const int WALK8INDEXES[] = {4, 8, 12, 0};
const int WALK12INDEXES[] = {5, 9, 13, 1};
	
//enum Oriet {LEFT, RIGHT, UP, DOWN,  UL, UR, DL, DR}; 
int Animation::getThetaIndex(float theta){	
	loop360(theta);
	if (type == CYCLIC) {
		if (theta > 180 && theta < 360)
			return -16;
		else
			return 0;
	}
	Oriet o = facing(theta);
	if (type == WALK8) return WALK8INDEXES[o];	
	if (type == WALK12) return WALK12INDEXES[o];
	return 1;
 }

void Animation::setTPF(int s){	tpf = s;}

Oriet facing(float theta){
	//loop360(theta);
	Oriet o = DOWN;
	if (theta <= 135 && theta > 45)			o = LEFT;	//left
	else if (theta <= 225 && theta > 135)	o = UP;	//forward 
	else if (theta <= 315 && theta > 225)	o = RIGHT;	//right
	else if (theta <= 45 && theta >= 0 || theta < 360 && theta > 315) o = DOWN;//backward

	return o;
}

