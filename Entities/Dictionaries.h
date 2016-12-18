#ifndef DICTIONARIES_H
#define DICTIONARIES_H

#include "../Template/SubObj.h"
#include "../Components/State.h"
#include "../Components/Rendering.h"
#include "../Components/Animation.h"
#include "../Components/Motion.h"
#include "../Components/Size.h"
#include "../Components/Health.h"

#include "../../Display/ModelManager.h"
//********************************* CONSTANTS *********************************

//enum EntityType {PROP, PARTICLE, ACTOR};   

struct EntityXZ{
	ID id;
	float x;
	float z;
};


//********************************* ABSTRACT *********************************

class Dictionary	{ 
public:


	
	void Dictionary::addProfile(ShaderProfile sp){profile.push_back(sp);}
	void Dictionary::addIdentity(Identity id){identity.push_back(id);}
	void Dictionary::addSize(Size s){size.push_back(s);}
	void Dictionary::addHealth(Health h){health.push_back(h);}
	
	ShaderProfile Dictionary::getProfile(ID id){ return profile[id];}
	Identity & Dictionary::getID(ID id){return identity[id];}
	float Dictionary::getCol(ID id);
	float Dictionary::getSep(ID id){return size[id].sepR;}
	float Dictionary::getAvo(ID id){return size[id].avoR;}
	Size Dictionary::getSize(ID id){return size[id];}

	ID Dictionary::getIndex(string name);
	
	ID Dictionary::profileCount(){return profile.size();}
	
	
	vector <Identity> identity; 	
	vector <ShaderProfile> profile; 
	vector <Size> size; 
	vector <Health> health; 
};

//********************************* PROPS *********************************

class PropList	: public Dictionary { 
	public:
		 
	void addProfileIndex(ID id){profileIndex.push_back(id);}
	void addRendering(Rendering r){rendering.push_back(r);}
	vector <ID> profileIndex; 
	//	vector <ID> animIndex; 
	//vector <Animation> anim;	
	vector <Rendering> rendering; 
};

//********************************* PARTICLES *********************************

class ParticleList : public Dictionary { 
	public:
	
	void addMotion(MotionMax mm){max.push_back(mm);}
		vector <ID> auxTex;
		vector <float> scale;
		vector <Animation> anim;
		vector <MotionMax> max; 		
		
};



#endif