#ifndef PROPS_H
#define PROPS_H

#include "Dictionaries.h"
#include "../Components/Location.h"
//********************************* CONSTANTS *********************************


//********************************* INITIALIZATION *********************************

class Props {
	public: 
	Props::		Props(){dict = &propList;}
	virtual void Props ::	reserve (ID max);


	void Props::applyDict(Dictionary * d){dict = d;}
	Dictionary *  Props::getDict(){return dict;}


	bool Props:: add(ID id, Rendering& r, Location& l);
	ID Props:: nextFree();

	void Props::clear();
	virtual void Props::reset();
	virtual void Props::reset(ID id);

	
	virtual void Props ::	draw (ID id);	

	void Props::changeState(ID id, State * S){state[id] = S;}
	virtual bool Props ::canMove (){return false;}
	
	ID Props::getSizeIndex(ID id);




	//animation, texture
	vector<ID> type;
	vector<Rendering> rendering;
	vector<Animation> animation;
	vector<Location> location;
	ID count;
	
	vector<State*> state;
	static State off;
	static StillState still;
	Dictionary * dict;
};
#endif