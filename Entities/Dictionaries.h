#ifndef DICTIONARIES_H
#define DICTIONARIES_H

#include "Actors.h"

//********************************* CONSTANTS *********************************

enum EntityType {PROP, PARTICLE, ACTOR};   

struct Identity {
	string name;
	ID id;
	//EntityType type;
};

//********************************* INITIALIZATION *********************************

class Dictionary	{ 
	public:

	static ID Dictionary::getIndex(string name, vector<Identity> &id);
	
};

class PropList	: public Dictionary { 
	public:
		
	static vector <Identity> & getID(){return profiles;}

		static vector <Identity> profiles; 	
		static vector <Rendering> renders; 
};

class ParticleList : public Dictionary { 
	public:

	static vector <Identity> & getID(){return profiles;}
		static vector <Identity> profiles; 		
		static vector <ID> textures; 
		static vector <ID> auxTex;
		static vector <MotionMax> max; 		
		
	//static vector <string> actionType; 
	//static vector <string> aAnim; 
};

#endif