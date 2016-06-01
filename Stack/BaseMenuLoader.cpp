//********************************* INITIALIZATION *********************************
#include "BaseMenuLoader.h"

BaseMenuLoader::BaseMenuLoader(){
	cursorFile = "";
	
}

void BaseMenuLoader::registerRoot(StackCommand * m){
	if (m)
		rMenus.push_back(m);
}



void BaseMenuLoader::load(){
	try {		
		loadList("menulist.xml", "MenuList", "MenuFile", menuFiles);
	}catch(...){
		cout << "Menus did not load properly." << endl;
	}
	for (int i = 0; i < menuFiles.size(); i++){
		loadMenuTree(i);
	}
	loadCursors();
}//*/

void BaseMenuLoader::loadAuxillary(rapidxml::xml_node<> * node){
	rapidxml::xml_attribute<> * a;
	for (node; node; node = node->next_sibling()){
		string s = getText(node->name());
		a = node->first_attribute();
		if (s == "CursorFile" && a) {
			s = getText(a->name());
			if (s == "filename")
				cursorFile = getText(a->value());					
		}
	}
}



void BaseMenuLoader::loadMenuTree(ID id){
	if (id < menuFiles.size() && id < rMenus.size()){
		try {
			rapidxml::file<> xmlFile(menuFiles[id].c_str()); // Default template is char
			rapidxml::xml_document<> doc;
			doc.parse<0>(xmlFile.data());
			rapidxml::xml_node<> *list = doc.first_node();
			for (list = list->first_node(); list; list = list->next_sibling())
				loadMenu(id, list);
		}catch(...){
			cout << "Menu [" << id << "] did not load properly."<< endl;
		}
	}
}

void BaseMenuLoader::loadMenu(ID id, rapidxml::xml_node<> * node){
	rapidxml::xml_node<> *n;
	rapidxml::xml_attribute<> *a;
	string s = getText(node->name());
	
	bool success = true;
	if (s == "Menu"){ 
		Menu menu = buildMenu(node);
		for (n = node->first_node(); n; n = n->next_sibling()){
			if (getText(n->name()) == "Background"){
				for (a = n->first_attribute(); a; a = a->next_attribute()){
					s = getText(a->name());
					if (s == "filename"){
						menu.setBackground(loadTexture(a->value(), false));
						//success = true;
					}
					else if (s == "backdrop")
						menu.backdrop = getInt(a->value());					
				}
			}
			if (getText(n->name()) == "Cursor"){
				for (a = n->first_attribute(); a; a = a->next_attribute()){
					s = getText(a->name());
					if (s == "id")
						menu.cursorID = getInt(a->value());
					else if (s == "x")
						menu.cursor.x = getInt(a->value())*PIXELSCALE;		
					else if (s == "y" || s == "z")
						menu.cursor.z = getInt(a->value())*PIXELSCALE;				
				}
			}
			if (getText(n->name()) == "Flow"){
				bool f = false;
				for (a = n->first_attribute(); a; a = a->next_attribute()){
					if (getText(a->name()) == "func")
						f = getInt(a->value());
				}
				menu.func = f;
				menu.addFlow(getInt(n->value()));		
			}
		}
		if (success) rMenus[id]->addMenu(menu);
	}	
}


Menu BaseMenuLoader::buildMenu(rapidxml::xml_node<> * node){	
	rapidxml::xml_attribute<> *a;
	rapidxml::xml_node<> *n;
	Menu menu;
	string s;
	for (a = node->first_attribute(); a; a = a->next_attribute()){
		s = getText(a->name());
		if (s == "name")
			menu.name = getText(a->value());					
		else if (s == "timeout")
			menu.timeOut = getInt(a->value());					
		else if (s == "lineh")
			menu.lineH = getInt(a->value())*PIXELSCALE;					
		else if (s == "linew")
			menu.lineW = getInt(a->value())*PIXELSCALE;					
		else if (s == "maxindex")
			menu.maxIndex = getInt(a->value());	
	}

	return menu;
}


void BaseMenuLoader::loadCursors(){	
	if (cursorFile != ""){
		try {
			rapidxml::file<> xmlFile(cursorFile.c_str()); // Default template is char
			rapidxml::xml_document<> doc;	
			rapidxml::xml_node<> *n;
			rapidxml::xml_attribute<> *a;
			string s;

			doc.parse<0>(xmlFile.data());
			rapidxml::xml_node<> *list = doc.first_node();
			for (n = list->first_node(); n; n = n->next_sibling()){
				s = getText(n->name());
				if(s == "Cursor"){
					int index = 0; GLuint tex = 0;
					for (a = n->first_attribute(); a; a = a->next_attribute()){
						s = getText(a->name());
						if(s == "id"){
							index = getInt(a->value());
						}			
						else if(s == "filename"){
							tex = loadTexture(a->value(), false);
							Menu::createCursor(tex, index);
						}		
					}
				}
			}
		}catch(...){
			cout << "Cursors did not load properly." << endl;
		}
	}
}

void BaseMenuLoader::printList(){
	for (int i = 0; i < menuFiles.size(); i++){
		cout << menuFiles[i] << endl;
	}
}

void BaseMenuLoader::printMenu(int i){
	if (i < menuFiles.size()){


	}
}


