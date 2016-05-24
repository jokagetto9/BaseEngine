#ifndef DRAWPOOL_H
#define DRAWPOOL_H

#include "EntityDictionary.h"
//********************************* CONSTANTS *********************************


//********************************* INITIALIZATION *********************************

class DrawPool {
	public: 	

	void DrawPool :: activateTextures();

	void DrawPool ::clear();

	void DrawPool ::	batch (Actors& actors, float frameDelta);
	void DrawPool ::	batch (ID index, ID tex);

	void DrawPool ::	draw (Actors& actors);

	vector<ID> activeTex;
	vector<vector <ID>> batchDraw;
		 

};
#endif