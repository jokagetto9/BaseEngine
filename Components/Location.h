#ifndef TRANSLATION_H
#define TRANSLATION_H

#include "Component.h"  
#include "../Display/Camera.h"

//********************************* CONSTANTS *********************************

//********************************* INITIALIZATION *********************************


class Location: public Component  {
public:
	
	Location::Location();

	glm::vec3 Location::pos(){	return glm::vec3(x_, y_, z_);}
		
	void Location::	place(float x, float z){x_ = x; z_ = z; }
	void Location::	place(glm::vec3 p){x_ = p.x; z_ = p.z; y_ = p.y;}
	void Location::	push(float x, float z){	x_ += x; 	z_ += z; }
	void Location::	translate(){ glPushMatrix(); glTranslatef(x_, y_, z_);}
	void Location::	adjustPos(Drctn d, float dist);

	bool  Location::withinRange(glm::vec3 tPos, float range);
//********************************* MEMBER FUNCTIONS *********************************


	float x_, y_, z_;
	union {
		float theta;
		Drctn dir;
	};
};


#endif