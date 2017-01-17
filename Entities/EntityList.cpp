
//********************************* INITIALIZATION *********************************
#include "EntityList.h"

State  EntityList ::off;
StillState  EntityList ::still;
MotionState  EntityList::moving;
AttackState  EntityList::charge;
//vector<Dictionary *> EntityList::lib;


void EntityList::reserve(ID max){
	if (max < MAX_COMPONENTS){
		state.resize(max);
		gData.resize(max);

		rendering.resize(max);
		animation.resize(max);
		
		size.resize(max);
		location.resize(max);
		motion.resize(max);

		ai.resize(max);
		target.resize(max);
		collide.resize(max);
		swarm.resize(max);


		health.resize(max);
		clear();
	} 
}

void EntityList ::setGridSize(ID x, ID z){
	gridSize.x = x;	gridSize.z = z;
	clearGrid();
}

void EntityList ::clearGrid(){
	grid.clear();
	grid.resize(gridSize.x);
	for (ID x = 0; x < gridSize.x; x++){
		grid[x].resize(gridSize.z);
		for (ID z = 0; z < gridSize.z; z++){			
			grid[x][z] = NULL;
		}
	}
}
//********************************* RESET *********************************

void EntityList::reset(){
	count = 0;
	ID s = state.size();
	for (ID i = 0; i < s; i++){
		reset(i);
	}
}
void EntityList::reset(ID id){	
	target[id] = Target();
	motion[id] = Motion();
	animation[id] = Animation();
	gData[id] = GridData();
	collide[id].clear();
}

void EntityList::clear(){
	count = 0;
	ID s = state.size();
	for (ID i = 0; i < s; i++){
		state[i] = &off;
		gData[i] = GridData();
	}
}



//********************************* INSERT *********************************

ID EntityList:: nextFree(){
	ID s = state.size();
	for (ID i = 0; i < s; i++){
		if (!state[i]->on())
			return i;
	}
	return MAX_COMPONENTS;
}



//********************************* ACTIVATE *********************************


//********************************* DRAW *********************************



void EntityList ::	draw (ID id){
	int index = rendering[id].texIndex; 
	location[id].translate();	
		if (index < 0){
			index += 16;
			M->gridBO.flip(-1, 1);
		}
		ID start = 0;
		if (animation.size() > id)
			start = animation[id].start;
		M->gridBO.drawGrid(start + index);	
	glPopMatrix(); //}	
}


void EntityList ::	printGrid (){
	GridData * g;
	int c = 0;
	cout << endl;
	for (ID z = 0; z < gridSize.z; z++){
		for (ID x = 0; x < gridSize.x; x++){
			g = grid[x][z];
			while(g){
				g = g->next;
				c++;
			}
			cout << c << " ";	
			c = 0;
		}
		cout << endl;
	} 
}


//************************************************** UPDATE ***************************************************


void EntityList ::	refresh (ID id){
	if (getEnt(id) != 1){
		Rendering &r = rendering[id]; 
		Animation &a = animation[id]; 
		Location &t = location[id]; 
	
		int tweak = 0;
		if (!state[id]->still() && notZero(motion[id].speed)) 
			tweak = a.frameTick(delta);


		float camTheta = C->getCameraTheta(t.pos(), false);	
		camTheta -= t.theta;
		tweak += a.getThetaIndex(camTheta);
		rendering[id].texIndex = tweak;
	}
}

//************************************************** GET ***************************************************

Entity EntityList::getEntity(ID id){
	Entity e = {state[id], rendering[id], animation[id], location[id], motion[id], gData[id], collide[id], target[id], swarm[id], health[id]};
	return e;
}
glm::vec3 EntityList :: getPos(ID id){
	return location[id].pos();
}


//should be overidden function
XZI EntityList ::	getGridXZ(glm::vec3 pos){
	XZI xz;
	if(pos.x < 0)
		xz.x = -1;
	else
		xz.x = pos.x/16;
	
	if(pos.z < 0)
		xz.z = -1;
	else
		xz.z = pos.z/16; 

	xz.x += 1; xz.z += 1;
	if (xz.x < 0) xz.x = 0;
	else if (xz.x > gridSize.x-1) xz.x = gridSize.x-1;
	if (xz.z < 0) xz.z = 0;
	else if (xz.z> gridSize.z-1) xz.z = gridSize.z-1;
	return xz; 
}

//************************************************** SET ***************************************************

void EntityList::setTarget(ID id, glm::vec3 pos){
		target[id].setTarget(pos);
}

void EntityList::scaleMotion (ID id, glm::vec3 targ){
		glm::vec3 tempV = scaleVector(location[id].pos(), targ, 10);
		motion[id].setTarget(tempV);
		state[id] = &charge;
}

/************************************************** DICTIONARY ***************************************************

Dictionary * EntityList::getDict(ID e){
	if (e < lib.size()) 
		return lib.at(e);
	else{
		cout << "Dictionary " << e << " failed" ;
		cout << endl;
		return NULL;
	}
}


float EntityList::getColRad(GridData & g){
	Dictionary * d = getDict(g.ent);
	if (d)
		return d->getCol(g.type);
	else
		return 0;
}
float EntityList::getSepRad(GridData & g){
	Dictionary * d = getDict(g.ent);
	if (d)
		return d->getSep(g.type);
	else
		return 0;
}
*/

	