#ifndef ENTITYDICTIONARY_H
#define ENTITYDICTIONARY_H

#include "Actors.h"

//********************************* CONSTANTS *********************************

enum EntityType {PROP, PARTICLE, ACTOR};   

struct Identity {
	string name;
	ID id;
	//EntityType type;
};

//********************************* INITIALIZATION *********************************

class EntityDictionary {	public:

				
		static vector <Identity> props; 
		static vector <Rendering> pRenders; 

		static vector <Identity> actors; 		
		static vector <Rendering> aRenders; 
		//static vector <string> actionType; 
		//static vector <string> aAnim; 
		static vector <ID> auxTex;


};
#endif