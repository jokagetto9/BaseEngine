#include "CollisionGrid.h"
#include "../../Entities/MonsterBook.h"



void CollisionGrid ::init(ID x, ID z, ID n){
	grid.resize(x);
	for (ID i = 0; i < x; i++)
		grid[i].resize(z);
	XZI xz = {x, z};
	gridSize = xz;

	activeList.resize(n);
}

void CollisionGrid ::clear(){
	for (ID x = 0; x < gridSize.x; x++)
		for (ID z = 0; z < gridSize.z; z++)
			grid[x][z].clear();	
	
	for (ID i = 0; i < activeList.size(); i++)
		activeList[i].clear();	
}

void CollisionGrid ::	updateGrid (Props* props){
	ID s = ent->rendering.size();
	clear();
	for (ID i = 0; i < s; i++){
		if (ent->state[i]->on()){
			Ob o; o.pos = ent->location[i].pos() - C->corner();
			o.sizeP = 0; //add propList.sizeP
			XZI xz = getGridXZ(o.pos);
			grid[xz.x][xz.z].push_back(o);
		}
	}
}


void CollisionGrid ::	updateGrid (ID n){
	assert(n < activeList.size());
	assert(ent != NULL);
	ID s = ent->rendering.size();
	clear();
	for (ID i = 0; i < s; i++){
		if (ent->state[i]->on()){
			Ob o; o.pos = ent->location[i].pos();
			o.sizeP = 0;
			XZI xz = getGridXZ(o.pos - C->corner());
			grid[xz.x][xz.z].push_back(o);
			ent->obstacles[i].grid = xz;
			activeList[n].push_back(i);
		}
	}
}


XZI CollisionGrid ::	getGridXZ(glm::vec3 pos){
	XZI xz;
	xz.x = pos.x/16 + 1;
	xz.z = pos.z/16 + 1;
	if (xz.x < 0) xz.x = 0;
	else if (xz.x > gridSize.x-1) xz.x = gridSize.x-1;
	if (xz.z < 0) xz.z = 0;
	else if (xz.z> gridSize.z-1) xz.z = gridSize.z-1;
	return xz;
}

void CollisionGrid ::	updateObstacles (ID n){
	assert(n < activeList.size());
	assert(ent != NULL);

	for (ID i = 0; i < activeList[n].size(); i++){
		ID index = activeList[n][i];
		XZI g = ent->obstacles[i].grid;
		checkGrid(index, g.x, g.z);	
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
	ent->obstacles[index].clear();
	glm::vec3 pos = ent->location[index].pos();
	for (ID i = 0; i < grid[x][z].size(); i++){
		Ob o = grid[x][z][i];
		if(o.pos != pos){
			//applySizeProfile(o.sizeP);
			testRange(index, o);	
		}
	}
	int tx, tz;
	for (ID i = 0; i < 8; i++){		
		tx = x + ADJ_[i].x; 
		tz = z + ADJ_[i].z;
		if (tx > 0 && tx < gridSize.x && tz > 0 && tz < gridSize.z){
			for (ID i = 0; i < grid[tx][tz].size(); i++){
				Ob o = grid[tx][tz][i];
				//applySizeProfile(o.sizeP);
				testRange(index, o);
			}
		}
	}

}

void CollisionGrid:: testRange(ID index, Ob& o){
	glm::vec3 pos = ent->location[index].pos() ;
	float d = getDistSq(pos, o.pos);
	if (d > 0 && d < 10*10) 
		ent->obstacles[index].testObject(o.pos, d);
}



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
			truncate(sep, 1);
			ent->motion[index].targetV += sep;			
		}else {
			glm::vec3 coh = ent->obstacles[index].calcCoh(pos); 
			if (notZero(coh)){
				truncate(coh, 0.0001);
				ent->motion[index].targetV += coh;			
			}
		}
	}

	//a->motion[index].setSpeed
}




