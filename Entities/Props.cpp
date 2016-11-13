#include "Props.h"

State  Props ::off;
StillState  Props ::still;


Props::		Props(){
	dict = &propList;

}

void Props ::	reserve (ID max){
	if (max < MAX_COMPONENTS){
		type.resize(max);
		health.resize(max);
		rendering.resize(max);
		location.resize(max);
		gData.resize(max);
		state.resize(max);
		clear();
	} 
}

ID Props ::	createProp (PropList& list, EntityXZ ent){
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


bool Props:: add(ID id, Rendering& r, Location& l){
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


ID Props:: nextFree(){
	ID s = state.size();
	for (ID i = 0; i < s; i++){
		if (!state[i]->on())
			return i;
	}
	return MAX_COMPONENTS;
}



void Props::clear(){
	count = 0;
	ID s = state.size();
	for (ID i = 0; i < s; i++){
		state[i] = &off;
		gData[i] = GridData();
	}
}

void Props::reset(){
	count = 0;
	ID s = state.size();
	for (ID i = 0; i < s; i++){
		reset(i);
	}
}

void Props::reset(ID id){	 
	//rendering[id] = Rendering(PROP, 0, 0);
	state[id] = &off;
	gData[id] = GridData();
	location[id] = Location();
}



void Props ::	draw (ID id){
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


void Props ::	update(){
	ID s = state.size();
	for (ID i = 0; i < s; i++){
		if (gData[i].enabled)
			updateGrid(i);
	}
}

void Props ::	updateHP(){
	ID s = state.size();
	for (ID i = 0; i < s; i++){		
		if (state[i]->on()){
			if (health[i].update(1) == 0){
				state[i] = &off;
			}
		}
	}
}

glm::vec3 Props :: getPos(ID id){
	return location[id].pos();
}



ID Props::getSizeIndex(ID id){
	if (dict){
		ID i = type[id];
		return dict->getSizeIndex(i);
	}else
		return 0;
}




void Props::updateGrid(ID id){
	glm::vec3 pos = location[id].pos() - C->corner();
	if(gData[id].setGrid(getGridXZ(pos)))
		gData[id].updateData(grid);
}

//should be overidden function
XZI Props ::	getGridXZ(glm::vec3 pos){
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
	else if (xz.x > GRIDSIZE.x-1) xz.x = GRIDSIZE.x-1;
	if (xz.z < 0) xz.z = 0;
	else if (xz.z> GRIDSIZE.z-1) xz.z = GRIDSIZE.z-1;
	return xz; 
}


void Props ::	printGrid (){
	GridData * g;
	int c = 0;
	cout << endl;
	for (ID z = 0; z < GRIDSIZE.z; z++){
		for (ID x = 0; x < GRIDSIZE.x; x++){
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