#ifndef DRAWPOOL_H
#define DRAWPOOL_H

#include "EntityList.h"
//********************************* CONSTANTS *********************************

//********************************* INITIALIZATION *********************************

class DrawPool {
	public: 	
	DrawPool ::DrawPool();
	void DrawPool :: init(Dictionary * d);
	void DrawPool :: activateTextures();

	void DrawPool ::clear();
	
	void DrawPool ::	batch (EntityList* ent);
	void DrawPool ::	batch (EntityList* ent, float frameDelta);
	void DrawPool ::	batch (ID index, ID tex);

	void DrawPool ::	draw (EntityList* ent);

	vector<ID> activeProfiles;
	vector<vector <ID>> batchDraw;
	vector<ID> gearShift;
		 
	Dictionary * dict;
};
#endif