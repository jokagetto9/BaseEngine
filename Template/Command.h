#ifndef COMMAND_H
#define COMMAND_H

#include "../Entities/EntityList.h"

class Command {
public:
	virtual void exec(Entity& e) {};
};



class MoveCommand : public Command {
public:
  void exec(Entity& e){
	if (o != STOP){
		e.mot_.move(o); 
		e.st = &EntityList::moving;
	}else {
		e.mot_.halt();
		e.st = &EntityList::still;
	}
  }
	Oriet o;
};





#endif