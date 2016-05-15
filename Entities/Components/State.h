#ifndef STATE_H
#define STATE_H

#include "Component.h"


//********************************* CONSTANTS *********************************

//********************************* INITIALIZATION *********************************


class State: public Component  {
public:
	virtual bool on(){return false;}
	virtual bool still(){return true;}
	virtual bool charge(){return false;}
};

class StillState: public State  {
public:
	bool on(){return true;}
	bool still(){return true;}
	bool charge(){return false;}
};

class MotionState: public State  {
public:
	bool on(){return true;}
	bool still(){return false;}
	bool charge(){return false;}
};

class ChargeState: public State  {
public:
	bool on(){return true;}
	bool still(){return false;}
	bool charge(){return true;}
};

#endif