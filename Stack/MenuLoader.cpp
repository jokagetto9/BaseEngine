//********************************* INITIALIZATION *********************************
#include "MenuLoader.h"

MenuLoader::MenuLoader(){
	cursorFile = "";
	
}

void MenuLoader::registerRoot(StackCommand * m){
	if (m)
		rMenus.push_back(m);
}



void MenuLoader::load(){
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

void MenuLoader::loadAuxillary(rapidxml::xml_node<> * node){
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



void MenuLoader::loadMenuTree(ID id){
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

void MenuLoader::loadMenu(ID id, rapidxml::xml_node<> * node){
	rapidxml::xml_node<> *n;
	rapidxml::xml_attribute<> *a;
	string s = getText(node->name());
	Menu menu;
	bool success = false;
	if (s == "Menu"){ 
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
		for (n = node->first_node(); n; n = n->next_sibling()){
			if (getText(n->name()) == "Background"){
				for (a = n->first_attribute(); a; a = a->next_attribute()){
					s = getText(a->name());
					if (s == "filename"){
						menu.setBackground(loadTexture(a->value(), false));
						success = true;
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

void MenuLoader::loadCursors(){	
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

void MenuLoader::printList(){
	for (int i = 0; i < menuFiles.size(); i++){
		cout << menuFiles[i] << endl;
	}
}

void MenuLoader::printMenu(int i){
	if (i < menuFiles.size()){


	}
}


