#ifndef CAMERA_H
#define CAMERA_H

#include "../lib.h"

//********************************* CONSTANTS *********************************
		// screen size	



//********************************* EXTERNAL *********************************

void loop360(float &theta);
/*/ Purpose: ensure theta is within valid range
Parameter(s):  theta - facing direction -> 0 = SOUTH
Side Effects:  theta -> 0-359
/*/

glm::vec3 calcThetaV(float theta);
/*/ Purpose: convert theta into a xz vector 
Parameter(s):  theta - facing direction -> 0 = SOUTH
Precondition(s): N/A
Returns: N/A
Side Effects:  N/A
Triggers: loop360
/*/

float findTheta(glm::vec3 v);
/*/ Purpose: find theta from vector 
Parameter(s):  v - directional vector
Returns: theta - facing direction -> 0 = SOUTH
Triggers: loop360
/*/

void truncate(glm::vec3 &v, float max);
/*/ Purpose: scale vector to max
Parameter(s):  v - vector, max - max length of vector
Side Effects:  v is normalized and scaled
/*/

float distSQ(glm::vec3 p1, glm::vec3 p2);
/*/ Purpose: length of vector squared
Parameter(s):  v = p1 - p2
Returns: length of v squared
Triggers:  glm::length2
/*/



float getDistSq(glm::vec3 v1, glm::vec3 v2);
long getDistSq2(glm::vec3 v1, glm::vec3 v2);
bool notZero(glm::vec3 v);

glm::vec3 radialOffset(glm::vec3 o, float arc, float dist);

//********************************* INITIALIZATION *********************************
class Camera  {  
	public:	
		
	void Camera::init();
/*/ Purpose: init members 
Side Effects:  init dist, yPos
Triggers: setupOpenGL
/*/

	void Camera::setupOpenGL(); 
/*/ Purpose: init OpenGL view settings 
Side Effects:  init proj and view matrixes, 
	enables, anisotropic filtering, alpha blending, culling
/*/

	void Camera::quit(); 
/*/ Purpose: close camera 
Side Effects:  deletes instance
/*/
	

//********************************* CAMERA MOVEMENT *********************************

	void Camera::	pan(float frameDelta); 
/*/ Purpose: rotate camera left and right around focus point
Parameter(s): frameDelta - change per frame -> RIGHT is negative
Side Effects:  theta loops from 0-360
/*/

	void Camera::	zoom(float frameDelta);	 
/*/ Purpose: zoom camera 
Parameter(s):  frameDelta - change per frame -> UP is negative
Side Effects:  dist changes 20-80 
/*/
	
	void Camera:: setCursorPos(int x, int y);
	void Camera::		drawCursor();	
	
//********************************* CAMERA MODES *********************************

	void Camera::		enterPOI();		
	void Camera::		autoPan();


//********************************* UPDATES *********************************

	void Camera::update(glm::vec3 focusP); 
/*/ Purpose: update camera matrixes according to theta, dist
Parameter(s):  focusP - position of focus
Side Effects: 
	mode = 0 -> camera moves around focus
	mode = 1 -> camera locks in place, follows focus
/*/
	
	void Camera::   lockCameraPos(float x, float z, float y, float theta);	
// Side Effects:  mode = 1

	
	float Camera:: getCameraTheta(glm::vec3 p, bool overr);

//************************************************** MEMBERS ***************************************************
//private::
	float xPos, yPos, zPos;		//position in 3D space


	//camera view direction -> 0 = SOUTH;
	//IMPORTANT: affects direction of hero's movement
	//		affects rotation and texture of billboarded objects
	float theta, prevTheta;				
								
	float dist;					//distance from camera to focus
	
	int mode;				//camera position is locked	
	float lockTheta;		
	glm::vec3 lockPos;			//locked cam position 

	float mX, mY;

//********************************* MEMBER FUNCTIONS *********************************

	
	glm::vec3 Camera::	corner();	
	void Camera::	setTheta(float focus);	
	bool Camera::	checkTheta();	

	
void Camera::adjustPos(Drctn d, int dist);

//********************************* SINGLETON *********************************
	static Camera* Camera::I(){
		if(instance == 0){
			instance = new Camera();
			return instance;
		}return instance;	
	}

private:
	Camera::Camera(){}
	static Camera* instance ;
};
extern Camera* C;

#endif