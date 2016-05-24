#ifndef MENULOADER_H
#define MENULOADER_H
#include "Menu.h"
#include "MCommand.h"
#include "../XMLParser.h"

//********************************* CONSTANTS *********************************

//********************************* INITIALIZATION *********************************

class MenuLoader  : public XMLParser{
public: 
	MenuLoader::MenuLoader();

	void MenuLoader::registerRoot(StackCommand * m);


	void MenuLoader::load();
	void MenuLoader::loadMenuTree(ID id);
	void MenuLoader::loadMenu(ID id, rapidxml::xml_node<> * node);
	void MenuLoader::loadAuxillary(rapidxml::xml_node<> * node);
	void MenuLoader::loadCursors();

	void MenuLoader::printList();
	void MenuLoader::printMenu(int i);

private:
	vector <string> menuFiles;		
	vector <StackCommand *> rMenus;
	string cursorFile;


};
#endif