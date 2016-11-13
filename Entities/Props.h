#ifndef PROPS_H
#define PROPS_H

#include "Dictionaries.h"
#include "../Components/Location.h"
#include "../Components/GridData.h"
#include "../Components/Health.h"
//********************************* CONSTANTS *********************************

struct EntityXZ{
	ID id;
	int x;
	int z;
};

//********************************* INITIALIZATION *********************************

class Props {
	public: 
	Props::		Props();
	virtual void Props ::	reserve (ID max);
	ID Props ::	createProp (PropList& list, EntityXZ ent);


	void Props::applyDict(Dictionary * d){dict = d;}
	Dictionary *  Props::getDict(){return dict;}


	bool Props:: add(ID id, Rendering& r, Location& l);
	ID Props:: nextFree();

	void Props::clear();
	virtual void Props::reset();
	virtual void Props::reset(ID id);

	
	virtual void Props ::	draw (ID id);	
	
	virtual void Props ::	update();	
	virtual void Props ::	updateHP();	
	void Props::changeState(ID id, State * S){state[id] = S;}
	virtual bool Props ::canMove (){return false;}
	
	glm::vec3 Props ::getPos(ID id);
	ID Props::getSizeIndex(ID id);
	void Props::setGridSize(ID x, ID z);

	void Props::updateGrid(ID id);

	
	XZI Props ::	getGridXZ(glm::vec3 pos);
	
	void Props ::	printGrid ();

	//animation, texture
	vector<ID> type;
	vector<Health> health;
	vector<Rendering> rendering;
	vector<Animation> animation;
	vector<Location> location;
	vector<GridData> gData;
	
	VGrid grid;

	ID count;
	
	vector<State*> state;
	static State off;
	static StillState still;
	Dictionary * dict;
};
#endif