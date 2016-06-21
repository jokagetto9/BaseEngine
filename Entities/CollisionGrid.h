#ifndef COLLISIONGRID_H
#define COLLISIONGRID_H

#include "Particles.h"
//********************************* CONSTANTS *********************************

//********************************* INITIALIZATION *********************************

class CollisionGrid {
	public: 	
		
	void CollisionGrid ::init(ID x, ID z, ID n);
	void CollisionGrid ::clear();
		
	void CollisionGrid ::	addProps (Props* props);
	void CollisionGrid ::	addEntities (ID n);
	XZI CollisionGrid ::	getGridXZ(glm::vec3 pos);

	void CollisionGrid ::	updateObstacles (ID n);
	
	void CollisionGrid ::	checkGrid (ID index, ID x, ID z);
	void CollisionGrid ::	printGrid ();
	
	void CollisionGrid:: testRange(ID index, Ob& o);
	void CollisionGrid:: applyAdjustments(ID n);

	void CollisionGrid:: setActiveEnt(Particles* particles){ent = particles;}
	
	vector<vector <vector<Ob>>> grid;
	vector<vector <ID>> activeList;
	Particles * ent;
	
	XZI gridSize;
		 

};
#endif