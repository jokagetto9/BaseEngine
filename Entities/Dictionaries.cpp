#include "Dictionaries.h"

vector <Identity> PropList::profiles; 
vector <Rendering> PropList::renders; 

vector <Identity> ParticleList::profiles; 
vector <ID> ParticleList::textures; 
vector <ID> ParticleList::auxTex;
vector <MotionMax> ParticleList::max;


ID Dictionary::getIndex(string name, vector<Identity> &id){
	for (ID i = 0; i < id.size(); i++){
		if (name == id[i].name)
			return i;
	}
	return 0;
}
