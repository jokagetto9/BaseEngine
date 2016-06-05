#ifndef COLLISIONGRID_H
#define COLLISIONGRID_H

#include "Dictionaries.h"
//********************************* CONSTANTS *********************************

//********************************* INITIALIZATION *********************************

class CollisionGrid {
	public: 	
		
	void CollisionGrid ::clear();
		
	void CollisionGrid ::	updateGrid (Actors* actors);

	void CollisionGrid ::	updateObstacles ();
	
	void CollisionGrid ::	checkGrid (ID index, ID x, ID z);
	void CollisionGrid ::	printGrid ();

	void CollisionGrid:: testRange(ID index, glm::vec3 pos);
	void CollisionGrid:: applyAdjustments();

	vector<ID> grid[6][5] ;
	vector<ID> activeList; 
	Actors * a;
	Particles *pa;
	Props * pr;

		 

};
#endif