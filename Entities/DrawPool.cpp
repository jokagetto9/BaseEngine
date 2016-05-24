#include "DrawPool.h"

void DrawPool :: activateTextures(){
	ID s = EntityDictionary::aRenders.size();
	for (ID i = 0; i < s; i++){
		ID tex = EntityDictionary::aRenders[i].tex;
		activeTex.push_back(tex);
	}
	batchDraw.resize(s);
	//
}


void DrawPool ::clear(){
	for (ID i = 0; i < activeTex.size(); i++){
			batchDraw[i].clear();
	}
}

void DrawPool ::	batch (Actors& actors, float frameDelta){
	actors.delta = frameDelta;
	ID s = actors.rendering.size();
	clear();
	for (ID i = 0; i < s; i++){
		if (actors.state[i]->on()){
			actors.refresh(i);
			batch(i, actors.rendering[i].tex);
		}
	}
}


void DrawPool ::	batch (ID index, ID tex){
	for (ID i = 0; i < activeTex.size(); i++){
		if (tex == activeTex[i])
			batchDraw[i].push_back(index);
	}
}



void DrawPool ::	draw (Actors& actors){
	int s = batchDraw.size();	
	for (ID profile = 0; profile < s; profile++){
		if (profile == 0)
			M->gridBO.prepNPC(); //prep
		int s = batchDraw[profile].size();	
		for (ID i = 0; i < s; i++){
			actors.draw(batchDraw[profile][i]);
		}
	}
}



