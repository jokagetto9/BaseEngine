#ifndef GRIDDATA_H
#define GRIDDATA_H

#include "Location.h"

//********************************* CONSTANTS *********************************


//********************************* INITIALIZATION *********************************
class GridData;
typedef vector<vector <GridData *>> VGrid;

class GridData: public Component  {
public:
	
	GridData::GridData();
	GridData::GridData(ID i, ID e);
	
	bool GridData::setGrid(XZI g);
	void GridData::setGrid(VGrid g);


	void GridData ::	updateData (VGrid &grid);
	void GridData ::	removeData (VGrid &grid);
	XZI GridData ::	getGridXZ(XZI gridSize, glm::vec3 pos);


	bool enabled;
	
	ID id;
	int ent;
	XZI xz;
	XZI prevxz;
	
	GridData * next;	
	GridData * prev;
};

extern XZI GRIDSIZE; 


#endif