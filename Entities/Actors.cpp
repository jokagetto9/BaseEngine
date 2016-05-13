#include "Actors.h"

Actors ::		Actors (){
	rendering.reserve(30);
	translation.reserve(30);
	ai.reserve(30);
	physics.reserve(30);
}


Actors ::		Actors (ID reserve){
	rendering.reserve(reserve);
	translation.reserve(reserve);
	ai.reserve(reserve);
	physics.reserve(reserve);
}