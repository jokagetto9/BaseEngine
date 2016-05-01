#ifndef COMMAND_H
#define COMMAND_H

#include "../../../Nodes/Hero.h"

class Command {
public:
  virtual ~Command() {}
  virtual void exec(Hero& h) = 0;

};



class MoveCommand : public Command {
public:
  void exec(Hero& h){
	if (o != STOP)
		h.move(o); 
	else
		h.stop();
  }
	Oriet o;
};







#endif