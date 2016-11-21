
//********************************* INITIALIZATION *********************************
#include "EntityList.h"

State  EntityList ::off;
StillState  EntityList ::still;
MotionState  EntityList::moving;
AttackState  EntityList::charge;



void EntityList::reserve(ID max){
	if (max < MAX_COMPONENTS){
		type.resize(max);
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

bool EntityList:: add(ID id, Rendering& r, Location& l){
	ID i = nextFree(); 
	if (i < MAX_COMPONENTS){
		type[i] = id;
		rendering[i] = r;
		location[i] = l;
		health[i].health = 1;
		state[i] = &still;			
		gData[i] = GridData(i, 1);
		count++;
		return true;
	}
	return false;
}

ID EntityList ::	createProp (PropList& list, EntityXZ ent){
	ID i = nextFree(); 
	if (i < MAX_COMPONENTS){
		Rendering r;		Location l;
		type[i] = ent.id;
		//health[i] = list.maxHealth[ent.id];
		rendering[i] = list.rendering[ent.id];
		location[i].place(ent.x, ent.z);
		health[i].health = 1;
		state[i] = &still;			
		gData[i] = GridData(i, 1);
		count++;
		return i;
	}
	return MAX_COMPONENTS;
}

ID EntityList ::	createParticle (ParticleList& list, EntityXZ ent){
	ID i = nextFree(); 
	if (i < MAX_COMPONENTS){
		Rendering r;		Location l;
		type[i] = ent.id;

		location[i].place(ent.x, ent.z);
		rendering[i].tex = list.getProfile(ent.id).tex;
		animation[i] = particleList.anim[ent.id];
		motion[i] = Motion(particleList.max[ent.id]);
		gData[i] = GridData(i, 2);
		health[i].set(12);
		health[i].setRate(-1);
		state[i] = &charge;
		count++;
		return i;
	}
	return MAX_COMPONENTS;
}


bool EntityList:: createActor(ID id, Rendering& r, Location& l, Motion &m, Animation &a){
	ID i = nextFree();
	if (i < MAX_COMPONENTS){
		type[i] = id;
		rendering[i] = r;
		location[i] = l;
		motion[i] = m;
		animation[i] = a;
		state[i] = &still;
		gData[i] = GridData(i, 3);
		count++;
		return true;
	}
	return false;
}

//********************************* ACTIVATE *********************************

void EntityList::setTarget(ID id, glm::vec3 pos){
	if (id < count)
		target[id].setTarget(pos);
}

void EntityList::activateAll(ID id){
	glm::vec3 pos = location[id].pos();
	for (ID i = 0; i < count; i++){
		if (gData[i].ent==3 && gData[i].id != id)
			target[i].setTarget(pos);
	}
}

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
	if (gData[id].ent != 1){
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

void EntityList ::	updateHP(){
	ID s = state.size();
	for (ID i = 0; i < s; i++){		
		if (state[i]->on()){
			if (health[i].update(1) == 0){
				state[i] = &off;
			}
		}
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
	//TODO if has target
	if (notZero(target[id].targetP)){
		glm::vec3 tempV = scaleVector(location[id].pos(), target[id].targetP, 0.1);
		motion[id].setTarget(tempV);
		state[id] = &charge;
		applyAIInteractions(id);
	}else{
		state[id] = &still;
	}
}
void EntityList:: applyAIInteractions(ID id){
	if( gData[id].ent > 1){
		swarm[id].reset();
		ID s = collide[id].size();
		for (ID i = 0; i < s; i++){	
			CollisionData cd = collide[id].getCollisionData(i);		
			swarm[id].calcSep(cd.dist, cd.distV);
		}
		swarm[id].normalizeVectors();
		if (notZero(swarm[id].sep.v)){
			glm::vec3 v = motion[id].targetV;
			v *= 0.01;
			motion[id].targetV = swarm[id].sep.v;	
			motion[id].targetV += v;
		}
	}

}


void EntityList::chargeParticle (ID id, glm::vec3 targ){
	if (id < count){
		glm::vec3 tempV = scaleVector(location[id].pos(), targ, 10);
		motion[id].setTarget(tempV);
		state[id] = &charge;
	}
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
						checkCollisions(g1->id, g2->id);
						g2 = g2->next;
					}
				}	
				g1 = g1->next;
			}
		}
}	

void EntityList:: checkCollisions(ID g1, ID g2){
	float d;
	glm::vec3 p1, p2, dv1, dv2;
	p1 = getPos(g1);
	p2 = getPos(g2);
	dv1 = p1 - p2;
	dv2 = p2 - p1;
	d = sqrt(getDistSq(p1, p2)); //-2
	
	if (d <= swarm[g2].coh.rad) {
		collide[g1].add(g1, g2, d, dv1); 
		collide[g2].add(g2, g1, d, dv2); 
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


void EntityList:: applyCollisions(ID id){
	if( gData[id].ent > 1){
		//swarm[id].reset();
		ID s = collide[id].size();
		for (ID i = 0; i < s; i++){	
			CollisionData cd = collide[id].getCollisionData(i);		
			if(cd.dist < swarm[id].col.rad){
				motion[id].backTrack(location[id], swarm[id].col.rat);
			}else {			
				//swarm[id].calcSep(cd.dist, cd.distV);
			}
		}
		//swarm[id].normalizeVectors();	
		//motion[id].targetV += swarm[id].sep.v;	
	}

}
//************************************************** GET ***************************************************

Entity EntityList::getEntity(ID id){
	Entity e = {state[id], location[id], motion[id], gData[id], collide[id], target[id], swarm[id], health[id]};
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

ID EntityList::getSizeIndex(ID id){
	if (dict){
		ID i = type[id];
		return dict->getSizeIndex(i);
	}else
		return 0;
}