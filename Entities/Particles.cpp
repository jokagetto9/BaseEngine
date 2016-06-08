#include "Particles.h"

Particles ::		Particles (){



}



//************************************************** DRAW *************************************************** 


void Particles ::	refresh (ID id){
	Rendering &r = rendering[id]; 
	Animation &a = animation[id]; 
	Location &t = location[id]; 
	
	int tweak = 0;
	if (!state[id]->still()) 
		tweak = a.frameTick(delta);


	float camTheta = C->getCameraTheta(t.pos(), false);	
	camTheta -= t.theta;
	tweak += a.getThetaIndex(camTheta);
	rendering[id].texIndex = tweak;
}


void Particles ::	draw (ID id){
	int index = rendering[id].texIndex; 
	location[id].translate();	
		if (index < 0){
			index += 16;
			M->gridBO.flip(-1, 1);
		}
		M->gridBO.drawx16(animation[id].start + index);	
	glPopMatrix(); //}	
}
