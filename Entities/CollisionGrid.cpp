#include "CollisionGrid.h"

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

void CollisionGrid ::	addProps(Props* props){
	ID s = props->rendering.size();
	for (ID i = 0; i < s; i++){
		if (props->state[i]->on()){
			Ob o; 
			o.sizeP = props->getSizeIndex(i);
			if (o.sizeP){
				o.pos = props->location[i].pos();			
				XZI xz = getGridXZ(o.pos - C->corner());
				grid[xz.x][xz.z].push_back(o);
			}
		}
	}
}

void CollisionGrid ::	addEntities (ID n){ 
	assert(n < activeList.size());
	assert(ent != NULL);
	ID s = ent->obstacles.size();
	for (ID i = 0; i < s; i++){
		if (ent->state[i]->on()){
			Ob o; 
			o.sizeP = ent->getSizeIndex(i);
			if (o.sizeP){
				o.pos = ent->location[i].pos();			
				XZI xz = getGridXZ(o.pos - C->corner());
				ent->obstacles[i].grid = xz;
				grid[xz.x][xz.z].push_back(o);
				activeList[n].push_back(i);
			}
		}
	}
}

XZI CollisionGrid ::	getGridXZ(glm::vec3 pos){
	XZI xz;
	xz.x = pos.x/16;
	xz.z = pos.z/16;
	xz.x += 1; xz.z += 1;
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
	for (ID z = 0; z < gridSize.x; z++){
		for (ID x = 0; x < gridSize.z; x++){
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
			ent->obstacles[index].testObject(pos, o);
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
				ent->obstacles[index].testObject(pos, o);
			}
		}
	}

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




