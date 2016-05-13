#include "Props.h"

Props ::		Props (){
	rendering.reserve(30);
	translation.reserve(30);
}


Props ::		Props (ID reserve){
	rendering.reserve(reserve);
	translation.reserve(reserve);
}



