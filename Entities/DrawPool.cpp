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

void DrawPool ::	batch (Props* ent){
	ID s = ent->rendering.size();
	clear();
	for (ID i = 0; i < s; i++){
		if (ent->state[i]->on()){
			batch(i, ent->rendering[i].tex);
		}
	}
}
void DrawPool ::	batch (Particles* ent, float frameDelta){
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


void DrawPool ::	batch (ID index, ID tex){
	for (ID i = 0; i < activeProfiles.size(); i++){
		if (tex == dict->getProfile(i).tex)
			batchDraw[i].push_back(index);
	}
}

void DrawPool ::	draw (Props* ent){
	ID s = batchDraw.size();	
	for (ID id = 0; id < s; id++){//prep
		int s = batchDraw[id].size();
		for (ID i = 0; i < s; i++){
			if (i == 0)
				M->gridBO.prep(dict->getProfile(id)); 
			ent->draw(batchDraw[id][i]);
		}
	}
}



