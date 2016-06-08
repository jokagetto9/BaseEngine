#include "Dictionaries.h"

vector <Identity> PropList::names; 
vector <Rendering> PropList::renders; 

vector <Identity> ParticleList::names;  
vector <ID> ParticleList::auxTex;
vector <Animation> ParticleList::anim;
vector <MotionMax> ParticleList::max;


ID Dictionary::getIndex(string name, vector<Identity> &id){
	for (ID i = 0; i < id.size(); i++){
		if (name == id[i].name)
			return i;
	}
	return 0;
}
