#include "Players.h"

void Players:: P1Update(float physDelta){
	update(P1, physDelta);
}

void Players:: P1aiUpdate(float aiDelta){	
	aiUpdate(P1, aiDelta);
}


void Players:: drawP1(float delta){	
	M->gridBO.prepHero();
	refresh(P1, delta);  
	draw(P1);	
}