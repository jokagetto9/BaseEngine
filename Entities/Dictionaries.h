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
		
	static vector <Identity> & getID(){return names;}

		static vector <Identity> names; 	
		static vector <Rendering> renders; 
};

class ParticleList : public Dictionary { 
	public:

	static vector <Identity> & getID(){return names;}
		static vector <Identity> names; 		
		static vector <ShaderProfile> profiles; 
		static vector <ID> auxTex;
		static vector <float> scale;
		static vector <Animation> anim;
		static vector <MotionMax> max; 		
		
	//static vector <string> actionType; 
	//static vector <string> aAnim; 
};

#endif