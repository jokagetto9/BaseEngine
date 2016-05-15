#ifndef PROPS_H
#define PROPS_H

#include "Components\State.h"
#include "Components\Rendering.h"
#include "Components\Animation.h"
#include "Components\Translation.h"
//********************************* CONSTANTS *********************************


//********************************* INITIALIZATION *********************************

class Props {
	public: 
	Props::		Props(){}
	virtual void Props ::	reserve (ID max);
	bool Props:: add(Rendering& r, Translation& t);
	ID Props:: nextFree();

	void Props::clear();
	virtual void Props::reset();
	virtual void Props::reset(ID id);

	void Props::changeState(ID id, State * S){state[id] = S;}

	//animation, texture
	vector<Rendering> rendering;
	vector<Animation> animation;
	vector<Translation> translation;
	
	static State off;
	static StillState still;
protected:

	vector<State*> state;
};
#endif