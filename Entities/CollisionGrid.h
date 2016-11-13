#ifndef COLLISIONGRID_H
#define COLLISIONGRID_H

#include "Actors.h"
#include "CollisionSet.h"
//********************************* CONSTANTS *********************************


//********************************* INITIALIZATION *********************************

class CollisionGrid {
	public: 	
		
	void CollisionGrid ::init(ID x, ID z, Props& pr, Particles& pa, Actors& ac);
	void CollisionGrid ::setGridSize(VGrid& g);
	
	void CollisionGrid:: checkCollisions(Props& pr, Particles& pa, Actors& ac);

	void CollisionGrid:: checkCollision(ID radsq, GridData* g1 , GridData* g2);	
	void CollisionGrid:: checkCollisions(GridData* g1, GridData* g2, CollisionSet* col);	
	


	float CollisionGrid ::getDistance(GridData* g1, GridData* g2);
	void CollisionGrid ::clear();
		
	void CollisionGrid:: applyAdjustments(ID n);
	

	Props * props;
	Particles * particles;
	Actors * actors;	

	CollisionSet collisions;

	XZI gridSize;
		 

};
#endif