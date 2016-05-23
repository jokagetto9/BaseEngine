//********************************* INITIALIZATION *********************************
#include "Rendering.h"

Rendering::Rendering(){
	type = PROP;
	profileIndex = 0;
	texIndex = 0;
	animIndex = -1;
}

Rendering::Rendering(EntityType e, ID id){	
	type = e;
	profileIndex = id;
	texIndex = 0;
	animIndex = -1;
}



Rendering::Rendering(EntityType e, ID id, ID tex){
	type = e;
	profileIndex = id;
	texIndex = tex;
	animIndex = -1;
}
