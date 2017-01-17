#ifndef ENTITYLIST_H
#define ENTITYLIST_H


#include "Dictionaries.h"
#include "../Components/GridData.h"
#include "../Components/Location.h"
#include "../Components/Motion.h"
#include "../Components/CollisionSet.h"
#include "../Components/AIBrain.h"
#include "../Components/Target.h"
#include "../Components/Swarming.h"
#include "../Components/Health.h"
#include "../Components/Damage.h"
#include "../Components/Properties.h"


//********************************* CONSTANTS *********************************



struct Entity {
	State * st;
	Rendering &ren_;
	Animation &ani_;
	Location &loc_;
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
	
	ID EntityList:: nextFree();

//********************************* DRAW *********************************
		
	virtual void EntityList ::	draw (ID id);		
	void EntityList ::	printGrid ();	


//************************************************** UPDATE ***************************************************
	
	void EntityList ::	refresh (ID id);

	
	void EntityList ::clearGrid();

	void EntityList::changeState(ID id, State * S){state[id] = S;}
		 
	

//************************************************** GET ***************************************************
	
	Entity EntityList::getEntity(ID id);
	ID EntityList::getEnt(ID id){return gData[id].ent;}
	virtual bool EntityList ::canMove (){return false;}
	
	glm::vec3 EntityList ::getPos(ID id);
	XZI EntityList ::	getGridXZ(glm::vec3 pos);
	ID EntityList::getSizeIndex(ID id);

//************************************************** DICTIONARY ***************************************************
	
	//static void EntityList ::	addDict (Dictionary* d){lib.push_back(d);}
	Dictionary * EntityList::getDict(ID e);

//************************************************** MEMBERS ***************************************************
	//animation, texture

	vector<State*> state;
	vector<GridData> gData; 

	vector<Rendering> rendering;
	vector<Animation> animation;
	
	vector<Size> size;
	vector<Location> location;
	vector<Motion> motion;

	vector<CollisionSet> collide; 
	
	vector<AIBrain> ai;
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


//********************************* MEMBER FUNCTIONS *********************************

	void EntityList ::	setState (ID eIndex, State* s){state[eIndex] = s;}
	void EntityList ::	setSize (ID eIndex, Size& s){size[eIndex] = s;}

	void EntityList ::	setDrawFeatures (ID eIndex, Rendering& r, Animation &a){rendering[eIndex] = r; animation[eIndex] = a;}
	
	void EntityList ::	place (ID eIndex, float x, float z){location[eIndex].place(x, z);}
	

	
	void EntityList::setTarget(ID id, glm::vec3 pos);
	void EntityList ::	setMotion (ID eIndex, Motion &m){motion[eIndex] = m;}
	void EntityList::	scaleMotion (ID id, glm::vec3 targ);
	void EntityList ::	setGridData (Identity& iden){gData[iden.index] = GridData(iden);}


	void EntityList ::	setHealth (ID eIndex, Health &h){health[eIndex] = h;}

	
	float EntityList ::	getInnerRad (ID eIndex){return size[eIndex].innerRad;}
	float EntityList ::	getOuterRad (ID eIndex){return size[eIndex].outerRad;}


};
#endif