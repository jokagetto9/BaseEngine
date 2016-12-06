#ifndef ENTITYLIST_H
#define ENTITYLIST_H


#include "Dictionaries.h"
#include "../Components/Location.h"
#include "../Components/Motion.h"
#include "../Components/GridData.h"
#include "../Components/CollisionSet.h"
#include "../Components/Target.h"
#include "../Components/Swarming.h"
#include "../Components/Health.h"

//********************************* CONSTANTS *********************************



struct Entity {
	State * st;
	//vector<Rendering> rendering;
	//vector<Animation> animation;
	Location &pos_;
	Motion &mot_;
	GridData& dat_; 
	CollisionSet& col_;
	Target &tar_;
	Swarming& ai_;
	Health& hea_;
};

//********************************* INITIALIZATION *********************************

class EntityList {
	public: 
	EntityList::	EntityList(){}
	virtual void EntityList ::	reserve (ID max);
	
	void EntityList ::setGridSize(ID x, ID z);
//********************************* RESET *********************************

	virtual void EntityList::reset();
	virtual void EntityList::reset(ID id);
	
	void EntityList::clear();

//********************************* INSERT *********************************
	
	ID EntityList:: nextFree();
	ID EntityList ::	createProp (PropList& list, EntityXZ ent);
	ID EntityList ::	createParticle (ParticleList& list, EntityXZ ent);		
	ID EntityList:: createActor(ParticleList& list, EntityXZ ent);

	ID EntityList:: createActor(Identity& id, Rendering& r, Location& l, Motion &m, Animation &a);

	

//********************************* ACTIVATE *********************************
	
	void EntityList::setTarget(ID id, glm::vec3 pos);
	void EntityList::activateAll(ID id);

//********************************* DRAW *********************************
		
	virtual void EntityList ::	draw (ID id);		
	void EntityList ::	printGrid ();	


//************************************************** UPDATE ***************************************************
	
	void EntityList ::	refresh (ID id);
	virtual void EntityList ::	update();	
	void EntityList ::	update (float physDelta);
	void EntityList ::	update (ID id);
	void EntityList::updateGrid(ID id);
	
	void EntityList ::clearGrid();
	
	void EntityList ::	aiUpdate (float aiDelta);
	void EntityList ::	aiUpdate (ID id);
	
	void EntityList:: applyAIInteractions(ID id);

	void EntityList::changeState(ID id, State * S){state[id] = S;}
		 
	void EntityList::chargeParticle (ID id, glm::vec3 targ);
	

//************************************************** COLLISION ***************************************************
		
	void EntityList:: checkCollisions();
	void EntityList:: checkCollisions(ID g1, ID g2);
	void EntityList:: applyCollisions();
	void EntityList:: applyCollisions(ID id);

//************************************************** GET ***************************************************
	
	Entity EntityList::getEntity(ID id);
	ID EntityList::getEnt(ID id){return gData[id].ent;}
	virtual bool EntityList ::canMove (){return false;}
	
	glm::vec3 EntityList ::getPos(ID id);
	XZI EntityList ::	getGridXZ(glm::vec3 pos);
	ID EntityList::getSizeIndex(ID id);

//************************************************** DICTIONARY ***************************************************
	
	static void EntityList ::	addDict (Dictionary* d){lib.push_back(d);}
	Dictionary * EntityList::getDict(ID e);
	float EntityList::getColRad(GridData & g);
	float EntityList::getSepRad(GridData & g);

//************************************************** MEMBERS ***************************************************
	//animation, texture

	vector<ID> type;
	vector<State*> state;

	vector<Rendering> rendering;
	vector<Animation> animation;

	vector<Location> location;
	vector<Motion> motion;

	vector<GridData> gData; 
	vector<CollisionSet> collide; 

	vector<Target> target;
	vector<Swarming> swarm;

	vector<Health> health;
	

	float delta;
		 
	VGrid grid;
	XZI gridSize;
	ID count;		


	Subject death;


	static State off;
	static StillState still;
	static MotionState moving;
	static AttackState charge;
	static vector<Dictionary *> lib;

};
#endif