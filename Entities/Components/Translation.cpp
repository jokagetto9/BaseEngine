//********************************* INITIALIZATION *********************************
#include "Translation.h"

Translation::Translation(){		
	x_ = 0; 	z_ = 0;		y_ = 0;
	//scale = 1; 
	//dir = DUNNO;
	theta = 0;
}


void Translation::adjustPos(Drctn d, float dist){	
	x_ += ADJ_[d].x * dist;	
	z_ += ADJ_[d].z * dist; 
}



Oriet Translation::	facing(){
	loop360(theta);
	Oriet o = DOWN;
	if (theta <= 135 && theta > 45)			o = LEFT;	//left
	else if (theta <= 225 && theta > 135)	o = UP;	//forward 
	else if (theta <= 315 && theta > 225)	o = RIGHT;	//right
	else if (theta <= 45 && theta >= 0 || theta < 360 && theta > 315) o = DOWN;//backward

	return o;
}