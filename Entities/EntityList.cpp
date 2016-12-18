
//********************************* INITIALIZATION *********************************
#include "EntityList.h"

State  EntityList ::off;
StillState  EntityList ::still;
MotionState  EntityList::moving;
AttackState  EntityList::charge;
vector<Dictionary *> EntityList::lib;


void EntityList::reserve(ID max){
	if (max < MAX_COMPONENTS){
		health.resize(max);
		rendering.resize(max);
		location.resize(max);
		gData.resize(max);
		state.resize(max);
		
		collide.resize(max);
		animation.resize(max);
		motion.resize(max);
		swarm.resize(max);
		target.resize(max);
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


//************************************************** AI ***************************************************

void EntityList ::	aiUpdate (float aiDelta){
	delta = aiDelta;
	ID s = state.size();
	for (ID i = 0; i < s; i++){
		if (state[i]->on()){
			aiUpdate(i);
		}
	}
}
	
void EntityList ::	aiUpdate (ID id){

	if (notZero(target[id].targetP)){
		if  (gData[id].ent != 2){	//update target if not !!!targetlocked!!!
			glm::vec3 tempV = scaleVector(location[id].pos(), target[id].targetP, 0.1);
			motion[id].setTarget(tempV);
		}
		state[id] = &charge; //check set still 
		applyAIInteractions(id); //apply without target? !!!wary!!!
	}else if (gData[id].ent != 2){
		state[id] = &still;
	}

	//!!!DEATH!!!
	health[id].update(1);
	if (health[id].isDead()){
		death.notify(gData[id]);
		state[id] = &off;
		gData[id].disableData(grid);
	}


}
void EntityList:: applyAIInteractions(ID id){
	if( getEnt(id) == 3){
		float sepRad = 2;
		swarm[id].reset();
		ID s = collide[id].size();
		for (ID i = 0; i < s; i++){	
			CollisionData cd = collide[id].getCollisionData(i);	

			if (gData[cd.obj2].enabled){ 				// in case of deleted entities
				sepRad = getSepRad(gData[cd.obj2]);
				sepRad += getSepRad(gData[id]);
				sepRad /= 2;

				swarm[id].calcSep(sepRad, cd.dist, cd.distV);	
			}
		}
		swarm[id].normalizeVectors();
		if (notZero(swarm[id].sep.v)){
			glm::vec3 v = motion[id].targetV;
			v *= 0.04;
			motion[id].targetV = swarm[id].sep.v;	
			motion[id].targetV += v;
		}
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

void EntityList ::	update(){
	ID s = state.size();
	for (ID i = 0; i < s; i++){
		if (gData[i].enabled)
			updateGrid(i);
	}
}

void EntityList ::	update (float physDelta){	
	delta = physDelta;
	ID s = state.size();
	clearGrid();
	for (ID i = 0; i < s; i++){
		update(i);
	}
}

void EntityList ::	update (ID id){
	motion[id].updateSpeed(delta);
	if (!state[id]->still()){
		
		//TODO if stopped change to still
		motion[id].move(location[id]);		
		
	}
	if(gData[id].enabled){
		updateGrid(id);

	}
	//TODO world wrap	
	//NEWBRANCH quadtree
}

void EntityList::updateGrid(ID id){
	collide[id].clear();
	glm::vec3 pos = location[id].pos() - C->corner();
	if(gData[id].setGrid(getGridXZ(pos)))
		gData[id].updateData(grid);
}


//************************************************** COLLISION ***************************************************


void EntityList:: checkCollisions(){
	GridData * g1 = NULL;	
	GridData * g2 = NULL;
	bool actors;
	for (ID x = 0; x < gridSize.x; x++)
		for (ID z = 0; z < gridSize.z; z++){
			XZI xz;
			g1 = grid[x][z];
			while (g1){
				for (int adj = -2; adj < 8; adj+=2) {
					if (adj < 0){
						g2 = g1->next;
					}else{
						xz.x = x+ADJ_[adj].x;
						xz.z = z+ADJ_[adj].z;
						if (xz.x >= 0 && xz.z >= 0 && xz.x < gridSize.x && xz.z < gridSize.z)
							g2 = grid[xz.x][xz.z];
						else 
							g2 = NULL;
					}
					while(g2){		
						
						if ( g1 == g2){
							cout << "Train Wreck ";
							cout << g1->xz.x << ", " << g1->xz.z << "     " ;
							cout << g2->xz.x << ", " << g2->xz.z  ;
							cout << endl;
						}
						checkCollisions(g1->index, g2->index);
						g2 = g2->next;
					}
				}	
				g1 = g1->next;
			}
		}
}	

void EntityList:: checkCollisions(ID g1, ID g2){
	
	try{
		float d;
		glm::vec3 p1, p2, dv1, dv2;
		p1 = getPos(g1);
		p2 = getPos(g2);
		dv1 = p1 - p2;
		dv2 = p2 - p1;
		d = sqrt(getDistSq(p1, p2)); //-2
		if (d <= swarm[g2].coh.rad && g1 != g2) {
			collide[g1].add(g1, g2, d, dv1); 
			collide[g2].add(g2, g1, d, dv2); 
			//prevent double collisions
		}
	}catch(...){
		cout << g1 << ", " << g2 << "collision failure." ;
		cout << endl;
	}
	/*// col, sep, avo, ali, coh
	
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

//*/

}

void EntityList:: applyCollisions(){
	ID s = state.size();
	for (ID i = 0; i < s; i++){		
		if (state[i]->on()){
			applyCollisions(i);
		}
	}
}

//!!!COLLISION!!!SHIT!!!
void EntityList:: applyCollisions(ID id){
	float colRad = 1.2;
	ID s = collide[id].size();
	for (ID i = 0; i < s; i++){	
		CollisionData cd = collide[id].getCollisionData(i);	
		int damage = 0;		
		colRad = getColRad(gData[id]);
		colRad += getColRad(gData[cd.obj2]);
		colRad /= 2;
				
		if(cd.dist < colRad){
			if (getEnt(id) == 1 && gData[cd.obj2].ent == 2){
				health[id].health -= 3;
		//1 and 3 /if damaging
			}else if (gData[id].ent == 2 && gData[cd.obj2].ent == 1){
				//if consuming and consumable
				health[id].kill();
			}else if (gData[id].ent == 2 && gData[cd.obj2].ent == 2){ 
				// lasers cant hit lasers //bullets can though				
			}else if (gData[id].ent == 2 && gData[cd.obj2].ent == 3 ){
				//if consuming and consumablew
				health[id].kill();
			}else if (gData[id].ent == 2 && gData[cd.obj2].ent == 4) {
				//particle hits player - source dependent
		//3 and 1 //if damaging
			}else if (gData[id].ent == 3 && gData[cd.obj2].ent == 2){
				//e2 damaging and e1 damageable
				//damage calc - defense vs power
				//damage animation if powerful
				health[id].health -= 5;
				//target[id].noTarget();
				motion[id].backTrack(location[id], swarm[id].col.rat);
				glm::vec3 p = motion[cd.obj2].speed;
				//p *= 5;
				location[id].push(p);
		//3 and 3

			}else if (gData[id].ent == 3 && gData[cd.obj2].ent == 4){ 
				//damage++;
				//cout << damage << endl;
				//hero hits enemy - enemy dependent
		//4 and 1
			}else if (gData[id].ent == 4 && gData[cd.obj2].ent == 2){ 
				//hero hits particle - enemy dependent
			}else if (gData[id].ent == 4 && gData[cd.obj2].ent == 3){ 
				health[0].health--;
				//hero hits enemy - enemy dependent
			}else {		
				// if e2.halting and e1.haltable			
				motion[id].backTrack(location[id], swarm[id].col.rat);
			}
		}
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

//************************************************** DICTIONARY ***************************************************

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

	