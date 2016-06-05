#ifndef DRAWPOOL_H
#define DRAWPOOL_H

#include "Dictionaries.h"
//********************************* CONSTANTS *********************************

//********************************* INITIALIZATION *********************************

class DrawPool {
	public: 	

	void DrawPool :: activateTextures();

	void DrawPool ::clear();

	void DrawPool ::	batch (Actors* actors, float frameDelta);
	void DrawPool ::	batch (ID index, ID tex);

	void DrawPool ::	draw (Actors* actors);

	vector<ID> activeProfiles;
	vector<vector <ID>> batchDraw;
	vector<ID> gearShift;
		 

};
#endif