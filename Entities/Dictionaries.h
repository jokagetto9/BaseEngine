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

	Size Dictionary::getSize(ID id){return size[id];}
	

	ID Dictionary::getIndex(string name){
		for (ID i = 0; i < identity.size(); i++){
			if (name == identity[i].name)
				return i;
		}
		return 0;
	}

	
	ID Dictionary::profileCount(){return profile.size();}
	
	
	vector <Animation> anim;	
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
	vector <Rendering> rendering; 
};

//********************************* PARTICLES *********************************

class ParticleList : public Dictionary { 
	public:
	
	void addMotion(MotionMax mm){max.push_back(mm);}
		vector <ID> auxTex;
		vector <float> scale;
		vector <vector <Animation>> auxAnim;
		vector <MotionMax> max; 		
		
};



#endif