#ifndef COLLISIONGRID_H
#define COLLISIONGRID_H

#include "Dictionaries.h"
//********************************* CONSTANTS *********************************
struct Ob {
	glm::vec3 pos;
	ID sizeP;
	//size scale
};
//********************************* INITIALIZATION *********************************

class CollisionGrid {
	public: 	
		 CollisionGrid ::CollisionGrid(){ent=NULL;}
	void CollisionGrid ::init(ID x, ID z, ID n);
	void CollisionGrid ::clear();
		
	void CollisionGrid ::	updateGrid (Props* props);
	void CollisionGrid ::	updateGrid (ID n);

	void CollisionGrid ::	updateObstacles (ID n);
	virtual XZI CollisionGrid ::	getGridXZ(glm::vec3 pos);
	
	void CollisionGrid ::	checkGrid (ID index, ID x, ID z);
	void CollisionGrid ::	printGrid ();

	void CollisionGrid:: testRange(ID index, Ob& o);
	void CollisionGrid:: applyAdjustments(ID n);
	
	void CollisionGrid:: setActiveEnt(Particles* particles){ent = particles;}

	vector<vector <vector<Ob>>> grid;
	vector<vector <ID>> activeList;

	Particles *ent;
	XZI gridSize;

};
#endif