#ifndef TRANSLATION_H
#define TRANSLATION_H

#include "Component.h"


//********************************* CONSTANTS *********************************

//********************************* INITIALIZATION *********************************


class Translation: public Compoment  {
public:
	
	Translation::Translation();

	glm::vec3 Translation::pos(){	return glm::vec3(x, y, z);}
		
	void Translation::	push(int x, int z){	x += x; 	z += z; y += 0; }
	void Translation::	translate(){ glPushMatrix(); glTranslatef(x, 0, z);}
	void Translation::adjustPos(Drctn d, int dist);

	float x, y, z;
	//float scale?
	union {
		float theta;
		Drctn dir;
	};
};


#endif