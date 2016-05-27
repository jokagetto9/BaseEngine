#include "DrawPool.h"

void DrawPool :: activateTextures(){
	ID s = ParticleList::profiles.size();
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

void DrawPool ::	batch (Actors* actors, float frameDelta){
	actors->delta = frameDelta;
	ID s = actors->rendering.size();
	clear();
	for (ID i = 0; i < s; i++){
		if (actors->state[i]->on()){
			actors->refresh(i);
			batch(i, actors->rendering[i].tex);
		}
	}
}


void DrawPool ::	batch (ID index, ID tex){
	for (ID i = 0; i < activeProfiles.size(); i++){
		if (tex == ParticleList::profiles[i].tex)
			batchDraw[i].push_back(index);
	}
}



void DrawPool ::	draw (Actors* actors){
	ID s = batchDraw.size();	
	for (ID id = 0; id < s; id++){
		M->gridBO.prep(ParticleList::profiles[id]); //prep
		int s = batchDraw[id].size();	 
		for (ID i = 0; i < s; i++){
			actors->draw(batchDraw[id][i]);
		}
	}
}



