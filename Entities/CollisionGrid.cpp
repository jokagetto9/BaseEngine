#include "CollisionGrid.h"

void CollisionGrid ::init(ID x, ID z, Props& pr, Particles& pa, Actors& ac){	
	gridSize.x = x;
	gridSize.z = z;	

	pr.grid.resize(gridSize.x);
	pa.grid.resize(gridSize.x);
	ac.grid.resize(gridSize.x);
	for (ID i = 0; i < gridSize.x; i++){
		pr.grid[i].resize(gridSize.z);
		pa.grid[i].resize(gridSize.z);
		ac.grid[i].resize(gridSize.z);
	}
}

void CollisionGrid ::setGridSize(VGrid& g){
	g.resize(gridSize.x);
	for (ID i = 0; i < gridSize.x; i++){
		g[i].resize(gridSize.z);
	}
}

void CollisionGrid ::clear(){
	for (ID x = 0; x < gridSize.x; x++)
		for (ID z = 0; z < gridSize.z; z++){
			//propGrid[x][z] ;
		}
}





/*/

void CollisionGrid:: applyAdjustments(ID n){
	assert(n < activeList.size());
	for (ID i = 0; i < activeList[n].size(); i++){
		ID index = activeList[n][i];
		glm::vec3 pos = ent->location[index].pos();
		glm::vec3 sep = ent->obstacles[index].calcSep(pos);
		if (notZero(sep)){
			if (ent->obstacles[index].collide(pos)){
				ent->motion[index].backTrack(ent->location[index]);
			}
			//truncate(sep, 1);
			ent->motion[index].targetV += sep;			
		}else {
			glm::vec3 coh = ent->obstacles[index].calcCoh(pos); 
			if (notZero(coh)){
				//truncate(coh, 0.001);
				ent->motion[index].targetV += coh;			
			}
		}
	}

	//a->motion[index].setSpeed
}



//*/
