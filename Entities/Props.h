#ifndef PROPS_H
#define PROPS_H

#include "Components\State.h"
#include "Components\Rendering.h"
#include "Components\Translation.h"
//********************************* CONSTANTS *********************************
const ID MAX_COMPONENTS = 10000;

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

	//animation, texture
	vector<Rendering> rendering;
	vector<Translation> translation;

protected:
	static State off;
	static StillState still;

	vector<State*> state;
};
#endif