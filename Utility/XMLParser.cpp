//********************************* INITIALIZATION *********************************
#include "XMLParser.h"


void XMLParser::loadList(char* listFile, string listTag, string fileTag, vector <string>& files){
    rapidxml::file<> xmlFile(listFile); // Default template is char
    rapidxml::xml_document<> doc;
	try {
		doc.parse<0>(xmlFile.data());
		rapidxml::xml_node<> *list = doc.first_node();
		rapidxml::xml_node<> *n;
		rapidxml::xml_attribute<> *a;
		string s = getText(list->name());
		if (s == listTag){ 
			for (n = list->first_node(); n; n = n->next_sibling()){
				s = getText(n->name());		
				a = n->first_attribute();
				if (s == fileTag && a) {
					s = getText(a->value());
					files.push_back(s);
				}else 
					loadAuxillary(n);
			}
		}
	}catch(...){
		cout << listTag << " did not load properly." << endl;
	}
}



string XMLParser::getText(char * c){	
	stringstream ss; string s;
	ss << c;	 ss >> s;
	return s;
}


int XMLParser::getInt(char * c){	
	stringstream ss; int i;
	ss << c;	 ss >> i;
	if (i < -10000)
		return 0;
	else 
		return i;
}