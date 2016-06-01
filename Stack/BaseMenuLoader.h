#ifndef BASEMENULOADER_H
#define BASEMENULOADER_H
#include "Menu.h"
#include "MCommand.h"
#include "../XMLParser.h"

//********************************* CONSTANTS *********************************

//********************************* INITIALIZATION *********************************

class BaseMenuLoader  : public XMLParser{
public: 
	BaseMenuLoader::BaseMenuLoader();

	void BaseMenuLoader::registerRoot(StackCommand * m);


	void BaseMenuLoader::load();
	void BaseMenuLoader::loadMenuTree(ID id);
	void BaseMenuLoader::loadMenu(ID id, rapidxml::xml_node<> * node);
	Menu BaseMenuLoader::buildMenu(rapidxml::xml_node<> * node);


	void BaseMenuLoader::loadAuxillary(rapidxml::xml_node<> * node);
	void BaseMenuLoader::loadCursors();

	void BaseMenuLoader::printList();
	void BaseMenuLoader::printMenu(int i);

private:
	vector <string> menuFiles;		
	vector <PlayCommand *> rMenus;
	



	string cursorFile;


};
#endif