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
	Animation::Animation(ID t, ID min, ID max);
	//Animation:: Node(_sprite);
/*/ Purpose: default constructor /*/

	void Animation::init(AnimType t);
/*/ Purpose: init inherited members  
Side Effects: init tpf, theta - facing direction -> 0 = SOUTH
/*/
	
//********************************* DRAW *********************************
	
	void Animation::	draw(float frameDelta);
	void Animation::	draw(float camTheta, float frameDelta);
/*/ Purpose: draw sprite -> changes by theta and tpf
Parameter(s): camTheta -> camera theta, frameDelta -> frameTick adjustment
Precondition(s): Once per frame
Triggers: getDirection, if moving -> frameTick 
/*/

	int Animation::	frameTick(  float frameDelta);
/*/ Purpose: track repeating animation
Parameter(s): frameDelta -> frameTick adjustment
Precondition(s): tick and tpf are initialized
Returns: -1, 0, 1, 0...
Side Effects: tick increases by frameDelta
/*/
	
	int Animation::getThetaIndex(float theta);

	int type;
	ID start, end;
	float tick; 
	int tpf;


	void Animation::setTPF(int s);

};
#endif