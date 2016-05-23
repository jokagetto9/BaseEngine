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


