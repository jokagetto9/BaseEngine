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
	props = &pr;
	particles = &pa;
	actors = &ac;
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

void CollisionGrid:: checkCollisions(Props& pr, Particles& pa, Actors& ac){
	GridData * g1 = NULL;	
	GridData * g2 = NULL;
	bool actors;
	for (ID x = 0; x < gridSize.x; x++)
		for (ID z = 0; z < gridSize.z; z++){
			XZI xz;
			g1 = ac.grid[x][z];
			while (g1){
				for (int adj = -2; adj < 0; adj+=2) {
					if (adj == -2){ //current grid					
						g2 = g1->next;
						xz.x = 0;
						xz.z = 0;
					}else{
						xz.x = x+ADJ_[adj].x;
						xz.z = z+ADJ_[adj].z;
					}
					if (xz.x >= 0 && xz.z >= 0 && xz.x < gridSize.x && xz.z < gridSize.z){ 
						g2 = ac.grid[xz.x][xz.z];
						checkCollisions(g1, g2, &collisions);

						//g2 = pa.grid[xz.x][xz.z];					
						//checkCollisions(g1, g2);

						//g2 = pr.grid[xz.x][xz.z];					
						//checkCollisions(g1, g2);
					}
				}	
				g1 = g1->next;
			}
			/*/
			g1 = pa.grid[x][z];
			while (g1){
				for (int adj = -2; adj < 0; adj+=2) {
					if (adj == -2){ //current grid					
						g2 = g1->next;
						xz.x = 0;
						xz.z = 0;
					}else{
						xz.x = x+ADJ_[adj].x;
						xz.z = z+ADJ_[adj].z;
					}
					if (xz.x >= 0 && xz.z >= 0 && xz.x < gridSize.x && xz.z < gridSize.z){ 
						g2 = pa.grid[xz.x][xz.z];					
						checkCollisions(g1, g2);

						g2 = pr.grid[xz.x][xz.z];					
						checkCollisions(g1, g2);
					}
				}	
				g1 = g1->next;
			}
			//*/
		}
}	
	
void CollisionGrid:: checkCollisions(GridData* g1, GridData* g2, CollisionSet* col){
	float d;
	while(g2){
		d = getDistance(g1, g2);
		if (d <= 2) {
			col->add(g1, g2);
		}
		//collect collisions
		g2 = g2->next;
	}
}

float CollisionGrid ::getDistance(GridData* g1, GridData* g2){
	float d = -1;
	if(g1 && g2){
		glm::vec3 p1, p2;
		if (g1->ent == 3){
			p1 = actors->getPos(g1->id);
		}else if (g1->ent == 2){
			p1 = particles->getPos(g1->id);
		} 
			
		if (g1->ent == 3){
			p2 = actors->getPos(g2->id);
		}else if (g1->ent == 2){			
			p2 = particles->getPos(g2->id);
		}else if (g1->ent == 2){			
			p2 = props->getPos(g2->id);
		}

		d = sqrt(getDistSq(p1, p2)); //-2
	}
	return d;
}



void CollisionGrid:: checkCollision(ID radsq, GridData* g1 , GridData* g2){
	while (g1){
		while(g2){
			g2 = g2->next;
		}
		g1 = g1->next; 
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
