#ifndef PROPS_H
#define PROPS_H

#include "../Components/State.h"
#include "../Components/Rendering.h"
#include "../Components/Animation.h"
#include "../Components/Location.h"
#include "../Components/Size.h"
#include "../../Display/ModelManager.h"
//********************************* CONSTANTS *********************************


//********************************* INITIALIZATION *********************************

class Props {
	public: 
	Props::		Props(){}
	virtual void Props ::	reserve (ID max);
	bool Props:: add(Rendering& r, Location& l);
	ID Props:: nextFree();

	void Props::clear();
	virtual void Props::reset();
	virtual void Props::reset(ID id);

	
	virtual void Props ::	draw (ID id);	

	void Props::changeState(ID id, State * S){state[id] = S;}

	//animation, texture
	vector<Rendering> rendering;
	vector<Animation> animation;
	vector<Location> location;
	vector<Size> size;
	ID count;
	
	static State off;
	static StillState still;
	vector<State*> state;

};
#endif