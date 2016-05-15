#ifndef COMMAND_H
#define COMMAND_H

#include "../Entities/Players.h"
#include "../Utility/Command.h"

class Command {
public:
  virtual ~Command() {}
  virtual void exec(Players& P) = 0;

};



class MoveCommand : public Command {
public:
  void exec(Players& P){
	if (o != STOP)
		P.motion[0].move(o); 
	else
		P.motion[0].halt();
  }
	Oriet o;
};







#endif