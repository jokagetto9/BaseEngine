#ifndef COMMAND_H
#define COMMAND_H

#include "../Entities/Players.h"
#include "../Utility/Command.h"

class Command {
public:
	//Command::Command(){PID = P1};
	virtual ~Command() {} 
  virtual void exec(Players& P) = 0;
  //ID PID;  
};



class MoveCommand : public Command {
public:
  void exec(Players& P){
	if (o != STOP){
		P.motion[P1].move(o); 
		P.changeState(P1, &Actors::walking);
	}else {
		P.motion[P1].halt();
		P.changeState(P1, &Props::still);
	}
  }
	Oriet o;
};







#endif