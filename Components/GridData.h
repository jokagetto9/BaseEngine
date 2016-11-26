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
	GridData::GridData(ID i, Identity& id);
	
	void GridData::reset();
	
	bool GridData::setGrid(XZI g);
	void GridData::setGrid(VGrid g);


	void GridData ::	updateData (VGrid &grid);
	void GridData ::	removeData (VGrid &grid);
	void GridData ::	disableData (VGrid &grid);
	XZI GridData ::	getGridXZ(XZI gridSize, glm::vec3 pos);
	
	string name;
	int index;
	int type;
	int ent;

	XZI xz;
	XZI prevxz;

	bool enabled;	

	GridData * next;	
	GridData * prev;
};



#endif