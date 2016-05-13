//********************************* INITIALIZATION *********************************
#include "Translation.h"

Translation::Translation(){		
	x = 0; 	z = 0;	y = 0;
	//scale = 1; 
	dir = DUNNO;
}


void Translation::adjustPos(Drctn d, int dist){	
	x += ADJ_[d].x * dist;	
	z += ADJ_[d].z * dist; 
}