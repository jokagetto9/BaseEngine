//********************************* INITIALIZATION *********************************
#include "GridData.h"


GridData::GridData(){
	reset();
}

void GridData::reset(){
	enabled = false;
	xz.x = -1; xz.z = -1;	
	prevxz.x = -1; prevxz.z = -1;	
	name = "";
	index = 0;	
	ent = -1;
	type = -1;
	next = NULL;	
	prev = NULL;
}

GridData::GridData(ID i, Identity &id){
	enabled = true;
	xz.x = -1; xz.z = -1;	
	prevxz.x = -1; prevxz.z = -1;
	
	name = id.name;
	index = i;	
	ent = id.ent;
	type = id.type;
	next = NULL;	
	prev = NULL;
}

bool GridData::setGrid(XZI g){
	if (xz.x == g.x && xz.z == g.z)
		return true;
	else {	
		prevxz.x = xz.x; prevxz.z = xz.z;
		xz.x = g.x; xz.z = g.z;	
	}
	return true;
}

void GridData ::	updateData (VGrid &grid){
	//removeData(grid);

	GridData * g = grid[xz.x][xz.z];
	if (g){
		GridData * pg = NULL;
		while (g){
			pg = g;
			g = g->next;
		}
		prev = pg;
		next = NULL;
		pg->next = this;
	}else{				
		grid[xz.x][xz.z] = this;
		prev = NULL;
		next = NULL;
	}
	 
}


void GridData ::	removeData (VGrid &grid){
	if (next){
		if (prev){
			prev->next = next;
			next->prev = prev;
		}else{
			grid[next->xz.x][next->xz.z] = next;
			next->prev = prev;
		}
	}else if(prev){
		prev->next = NULL;
	}else if (prevxz.x >= 0 && prevxz.z >= 0){
 		grid[prevxz.x][prevxz.z] = NULL;
	}
}


void GridData ::	disableData (VGrid &grid){
	removeData(grid);	reset();
}
