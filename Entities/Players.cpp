#include "Players.h"


void Players:: drawP1(float delta){	
	M->gridBO.prepHero();
	refresh(P1, delta); 
	draw(P1);	
}