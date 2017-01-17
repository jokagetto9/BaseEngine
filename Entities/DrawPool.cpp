#include "DrawPool.h"


DrawPool ::DrawPool(){
	dict = NULL;
}
void DrawPool :: init(Dictionary * d){
	if(dict != d){
		dict = d;
		activateTextures();
	}

}
  
void DrawPool :: activateTextures(){
	//activeProfiles.clear();
	ID s = dict->profileCount();
	for (ID i = 0; i < s; i++){
		activeProfiles.push_back(i);
	} 
	batchDraw.resize(s);
	//
}


void DrawPool ::clear(){
	for (ID i = 0; i < activeProfiles.size(); i++){
			batchDraw[i].clear();
	}
}



void DrawPool ::	batch (ID index, ID tex){
	for (ID i = 0; i < activeProfiles.size(); i++){
		if (tex == dict->getProfile(i).tex)
			batchDraw[i].push_back(index);
	}
}


void DrawPool ::	batch (EntityList* ent){
	ID s = ent->rendering.size();
	clear();
	for (ID i = 0; i < s; i++){
		if (ent->state[i]->on()){
			//ent->refresh(i);
			batch(i, ent->rendering[i].tex);
		}
	}
}

void DrawPool ::	batch (EntityList* ent, float frameDelta){
	ent->delta = frameDelta;
	ID s = ent->rendering.size();
	clear();
	for (ID i = 0; i < s; i++){
		if (ent->state[i]->on()){
			ent->refresh(i);
			batch(i, ent->rendering[i].tex);
		}
	}
}
void DrawPool ::	draw (EntityList* ent){
	ID profiles = batchDraw.size();	
	for (ID id = 0; id < profiles; id++){//prep
		int s = batchDraw[id].size();
		for (ID i = 0; i < s; i++){
			if (i == 0)
				M->gridBO.prep(dict->getProfile(id)); 
			ent->draw(batchDraw[id][i]);
		}
	}
}



/*/



void EntityList ::	draw (ID id){
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




void EntityList ::	refresh (ID id){
	if (getEnt(id) != 1){
		Rendering &r = rendering[id]; 
		Animation &a = animation[id]; 
		Location &t = location[id]; 
	
		int tweak = 0;
		if (!state[id]->still() && notZero(motion[id].speed)) 
			tweak = a.frameTick(delta);


		float camTheta = C->getCameraTheta(t.pos(), false);	
		camTheta -= t.theta;
		tweak += a.getThetaIndex(camTheta);
		rendering[id].texIndex = tweak;
	}
}

//*/