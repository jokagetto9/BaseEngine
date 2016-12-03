#ifndef COMMAND_H
#define COMMAND_H

#include "../Entities/EntityList.h"

class Command {
public:
	//Command::Command(){PID = P1};
	virtual ~Command() {} 
  virtual void exec(Entity& e) = 0;
  //ID PID;  
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