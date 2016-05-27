#ifndef ANIMATION_H
#define ANIMATION_H

#include "Translation.h"

//********************************* CONSTANTS *********************************
enum AnimType { CYCLIC, WALK8, WALK12};  


Oriet facing(float theta);
//********************************* EXTERNAL *********************************


//********************************* INITIALIZATION *********************************

class Animation{
public:

	Animation::Animation();

	void Animation::setCyclic(ID min, ID max, ID frames);
	
//********************************* DRAW *********************************
	
	void Animation::	draw(float frameDelta);
	void Animation::	draw(float camTheta, float frameDelta);


	int Animation::	frameTick(  float frameDelta);

	
	int Animation::getThetaIndex(float theta);

	int type;
	ID start, end;
	float tick; 
	int tpf;


	void Animation::setTPF(int s);

};
#endif