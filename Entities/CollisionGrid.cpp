#include "CollisionGrid.h"


void CollisionGrid ::clear(){
	for (ID x = 0; x < 6; x++)
		for (ID z = 0; z < 5; z++)
			grid[x][z].clear();		
	activeList.clear();
}

void CollisionGrid ::	updateGrid (Actors* actors){
	a = actors;
	ID s = actors->rendering.size();
	clear();
	for (ID i = 0; i < s; i++){
		if (actors->state[i]->on()){
			glm::vec3 p = a->location[i].pos() - C->corner();
			int x = p.x/16;
			int z = p.z/16;
			x += 1; z += 1;
			if (x < 0) x = 0;
			else if (x > 5) x = 5;
			if (z < 0) z = 0;
			else if (z > 4) z = 4;
			grid[x][z].push_back(i);
			activeList.push_back(i);
		}
	}
}


void CollisionGrid ::	updateObstacles (){
	for (ID x = 0; x < 6; x++){
		for (ID z = 0; z < 5; z++){
			for (ID i = 0; i < grid[x][z].size(); i++){
				ID index = grid[x][z][i];
				checkGrid(index, x, z);				
			}
		}
	}
	//printGrid ();
}


void CollisionGrid ::	printGrid (){
	cout << endl;
	for (ID z = 0; z < 5; z++){
		for (ID x = 0; x < 6; x++){
			cout << grid[x][z].size() << " ";	
		}
		cout << endl;
	}
}

void CollisionGrid ::	checkGrid (ID index, ID x, ID z){
	a->obstacles[index].clear();
	for (ID i = 0; i < grid[x][z].size(); i++){
		ID index2 = grid[x][z][i];
		if(index2 != index){
			glm::vec3 pos = a->location[index2].pos();
			testRange(index, pos);				
		}
	}
	int tx, tz;
	for (ID i = 0; i < 8; i++){		
		tx = x + ADJ_[i].x; 
		tz = z + ADJ_[i].z;
		if (tx > 0 && tx < 6 && tz > 0 && tz < 5){
			for (ID i = 0; i < grid[tx][tz].size(); i++){
				ID index2 = grid[tx][tz][i];
				glm::vec3 pos = a->location[index2].pos();
				testRange(index, pos);
			}
		}
	}

}

void CollisionGrid:: testRange(ID index, glm::vec3 pos){
	Location &l = a->location[index];
	float d = getDistSq(l.pos(), pos);
	if (d > 0 && d < 10*10) 
		a->obstacles[index].testObject(pos, d);
}



void CollisionGrid:: applyAdjustments(){
	for (ID i = 0; i < activeList.size(); i++){
		ID index = activeList[i];
		glm::vec3 pos = a->location[index].pos();
		glm::vec3 sep = a->obstacles[index].calcSep(pos);
		if (notZero(sep))
			a->motion[index].targetV += sep;
	}

	//a->motion[index].setSpeed
}




