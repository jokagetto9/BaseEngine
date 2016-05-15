#ifndef TRANSLATION_H
#define TRANSLATION_H

#include "Component.h"

#include "../../Stack/Camera.h"

//********************************* CONSTANTS *********************************

//********************************* INITIALIZATION *********************************


class Translation: public Component  {
public:
	
	Translation::Translation();

	glm::vec3 Translation::pos(){	return glm::vec3(x_, y_, z_);}
		
	void Translation::	place(float x, float z){x_ = x; z_ = z; }
	void Translation::	push(float x, float z){	x_ += x; 	z_ += z; }
	void Translation::	translate(){ glPushMatrix(); glTranslatef(x_, y_, z_);}
	void Translation::	adjustPos(Drctn d, float dist);


//********************************* MEMBER FUNCTIONS *********************************
	Oriet Translation::	facing();


	float x_, y_, z_;
	//float scale?
	union {
		float theta;
		Drctn dir;
	};
};


#endif