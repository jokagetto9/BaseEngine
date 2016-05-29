#ifndef MCOMMAND_H
#define MCOMMAND_H
#include "Menu.h"
#include "../BaseGameState.h"

//********************************* CONSTANTS *********************************

//********************************* INITIALIZATION *********************************


class PlayCommand  {
public:
  virtual void enter(vector <Menu *>& stack, int i){
	stack.clear();
	G->paused = false;
	G->state = PLAY;
  }
  
  virtual void addMenu(Menu& menu){}

  virtual int size(){return 0;}
};


class StackCommand : public PlayCommand{
public:
  virtual void enter(vector <Menu *>& stack, int i){
	  if (size() > i){
		stack.push_back(&menus[i]);		
		G->paused = true;
		if (G->state == PLAY)
			G->state = PAUSE;
	  }
  }

  void addMenu(Menu& menu){
	  menus.push_back(menu);
  }

  int size(){return menus.size();}

protected:
  vector<Menu> menus;  
};





class MenuCommand  {
public:
	virtual void exec(Menu * m){};
};
class MenuDrctn : public MenuCommand {
public:
	MenuDrctn::MenuDrctn(){reset();}
  void MenuDrctn::exec(Menu * m){
	  if (xz.x != 0)
		 m->cursorLR(xz.x);
	  else if (xz.z != 0)
		 m->cursorUD(xz.z);
	  reset();
  }
  void MenuDrctn::set(int x, int z){xz.x = x; xz.z = z;}
  void MenuDrctn::reset(){xz.x = 0; xz.z = 0;}

private: 
	XZI xz;
};

class MenuAccept : public MenuCommand  {
public:
  void exec(Menu * m){
	  m->enter();
  }
};

class MenuQuit : public MenuCommand   {
public:
  void exec(Menu * m){	  
	  m->quit();
  }
};



//class MessageCommand  {
//public:

//};

#endif