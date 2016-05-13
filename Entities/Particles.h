#ifndef PHYSICSSYSTEM_H
#define PHYSICSSYSTEM_H

#include "Components\Physics.h"
//********************************* CONSTANTS *********************************


//********************************* INITIALIZATION *********************************

class Actors {
	public: 
	Actors::		Actors();
	Actors ::		Actors (ID reserve);
	void Actors ::		genInteractions();	
	void Actors ::		trackInteractions();
		

	
	void Actors::		physUpdate(float delta);
	void Actors::		aiUpdate(float delta, glm::vec3 target);
	void Actors::		slowaiUpdate();
	void Actors ::		interact (int pid);


	void Actors ::		draw (float delta);
/*/ Purpose: 
Side Effects:  
Triggers: 
/*/
	
	void Actors::		purge();
//************************************************** MEMBERS ***************************************************
	
	//vector<NPC> npc;
	vector<Physics> components;

};
#endif