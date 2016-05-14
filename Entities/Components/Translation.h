#ifndef TRANSLATION_H
#define TRANSLATION_H

#include "Component.h"


//********************************* CONSTANTS *********************************

//********************************* INITIALIZATION *********************************


class Translation: public Component  {
public:
	
	Translation::Translation();

	glm::vec3 Translation::pos(){	return glm::vec3(x_, y_, z_);}
		
	void Translation::	place(int x, int z){x_ = x; z_ = z; }
	void Translation::	push(int x, int z){	x_ += x; 	z_ += z; }
	void Translation::	translate(){ glPushMatrix(); glTranslatef(x_, y_, z_);}
	void Translation::	adjustPos(Drctn d, int dist);

	float x_, y_, z_;
	//float scale?
	union {
		float theta;
		Drctn dir;
	};
};


#endif