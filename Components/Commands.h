#ifndef COMMANDS_H
#define COMMANDS_H

#include  "../Template/Command.h"


//********************************* CONSTANTS *********************************

//********************************* INITIALIZATION *********************************

class Commands: public Component  {
public:
	Commands:: Commands();
	Command * refresh;
	Command * animation;
	static Command nothing;
};


#endif