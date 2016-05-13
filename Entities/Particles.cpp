#include "Actors.h"

Actors ::		Actors (){
	components.reserve(30);
}
Actors ::		Actors (ID reserve){
	components.reserve(reserve);
}




void Actors::		physUpdate(float delta){
	int s = components.size();
	for (int i = 0; i < s; i++){
		//if(!components[i].dead)
			//components[i].physUpdate(500, delta);
	}
}
