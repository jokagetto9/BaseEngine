#ifndef COMMAND_H
#define COMMAND_H

#include "../Entities/Actors.h"
#include "../Utility/Command.h"

class Command {
public:
	//Command::Command(){PID = P1};
	virtual ~Command() {} 
  virtual void exec(Actor& a) = 0;
  //ID PID;  
};



class MoveCommand : public Command {
public:
  void exec(Actor& a){
	if (o != STOP){
		a.mot_.move(o); 
		a.st = &Actors::walking;
	}else {
		a.mot_.halt();
		a.st = &Props::still;
	}
  }
	Oriet o;
};

#endif