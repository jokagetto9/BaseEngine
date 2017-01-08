#include "Dictionaries.h"



ID Dictionary::getIndex(string name){
	for (ID i = 0; i < identity.size(); i++){
		if (name == identity[i].name)
			return i;
	}
	return 0;
}

