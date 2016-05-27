#ifndef XMLPARSER_H
#define XMLPARSER_H
#include "lib.h"

//********************************* CONSTANTS *********************************

//********************************* INITIALIZATION *********************************

class XMLParser  {
public: 
	void XMLParser::loadList(char* listFile, string listTag, string fileTag, vector <string>& files);
	string XMLParser::getText(char * c);
	int XMLParser::getInt(char * c);	
	float XMLParser::getFloat(char * c);


	void XMLParser::printList();

	virtual void loadAuxillary(rapidxml::xml_node<> * node){}
	
};
#endif