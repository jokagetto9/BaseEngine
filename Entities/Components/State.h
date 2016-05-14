#ifndef STATE_H
#define STATE_H

#include "Component.h"


//********************************* CONSTANTS *********************************

//********************************* INITIALIZATION *********************************


class State: public Component  {
public:
	virtual bool on(){return false;}
	virtual bool still(){return true;}
};

class StillState: public State  {
public:
	bool on(){return true;}
	bool still(){return true;}
};

class MotionState: public State  {
public:
	bool on(){return true;}
	bool still(){return false;}
};


#endif