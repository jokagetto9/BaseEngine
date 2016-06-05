
//********************************* INITIALIZATION *********************************
#include "Camera.h"
Camera* Camera::instance = 0;
Camera* C;

void Camera::init (){	
	//if(_DEBUG) cout << "Initializing Camera" << endl;
	//default is 35, 20 for now
	mode = 0;
	theta = 180; 	dist = 0 ;
	xPos = 0; zPos = 0;
	// camera distance	// 16x12	// 14x7
	yPos = 41.57;		// 51.9;  //43.2255;
	setupOpenGL();
}

void Camera::setupOpenGL(){
	//fixed function proj matrix - replace later
	glViewport(0, 0, dfWIDTH, dfHEIGHT);
	glMatrixMode(GL_PROJECTION); 
	glLoadIdentity();

	//fixed function view matrix - replace later
	gluPerspective(60, ASPECTR, 0.1, 1024);	
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	
	glEnable(GL_DEPTH_TEST);  glEnable(GL_TEXTURE_2D);

	//set anisotropic filtering to max
	GLfloat fLargest;
	glGetFloatv(GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT, &fLargest);

	//enable alpha blending
	glAlphaFunc(GL_GREATER, 0.3);
	glEnable(GL_ALPHA_TEST);	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA); 		
	//glBlendFunc(GL_ZERO, GL_SRC_COLOR); //stained glass effect

	//cull face settings
	//glEnable(GL_CULL_FACE); glCullFace(GL_BACK);


	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_DONT_CARE) ;
	
	//if(_DEBUG) cout << "Draw Mode Ready" << endl;
}

void Camera::quit(){delete instance; instance = NULL;}

//********************************* CAMERA FUNCTIONS *********************************

// pan camera in 360 degrees
void Camera::pan(float frameDelta){
	theta += TURN_RATE * frameDelta;	// camera turn rate
	loop360(theta);
}
// zoom camera in and out
void Camera::zoom(float frameDelta){	
	yPos += ZOOM_RATE * frameDelta;		// camera zoom rate
	if (yPos < 20 ) yPos = 20;		// zoom min
	if (yPos > 100) yPos = 100;		// zoom max
}//*/

//********************************* UPDATE *********************************
void Camera::update(glm::vec3 focusP){
	int defCamDist = 35; //default cam dist

	glm::vec3 offset = calcThetaV(0);		//calc rotation ratio
	offset.x *= dist;	offset.z *= dist;		//scale rotation to distance

	// calculate camera height -> ramp up effect
	offset.y = 0;
	int zoffSet = 12;
	// update view matrix
	if (mode == 1){
		gluLookAt(
			lockPos.x, lockPos.y, lockPos.z,			// x,y,z of eye
			focusP.x, lockPos.y, focusP.z,	// look at the focus 	// x,y,z of look at point
			0.0, 1.0, 0.0);					// always y = up..		// x,y,z of up vector

	}else{	
		xPos = focusP.x-offset.x; zPos = focusP.z-offset.z;
		/////////////////lookatpoint///////////////////////
		gluLookAt(
			focusP.x, yPos, focusP.z+zoffSet,			// x,y,z of eye
			focusP.x, focusP.y, focusP.z+zoffSet,	// look at the focus 	// x,y,z of look at point
			0.0, 0.0, -1.0);					// always y = up..		// x,y,z of up vector
	}

}

void Camera::   lockCameraPos(float x, float z, float y, float theta){
	mode = 1;
	lockTheta = theta;
	lockPos.x = x;		lockPos.z = z;		lockPos.y = y;	
}


float Camera:: getCameraTheta(glm::vec3 p, bool overr){
	if(C->mode == 1 || overr){
		glm::vec3 camV; 
		camV = p - lockPos;
		return findTheta(camV);
	}
	return theta;
}


//********************************* MEMBER FUNCTIONS *********************************
void Camera::setTheta(float focus){ theta = focus;}

bool Camera::	checkTheta(){
	bool t;
	t = prevTheta != theta;
	if (t) prevTheta = theta;
	return !t;
}

void Camera::adjustPos(Drctn d, int dist){
	lockPos.x += ADJ_[d].x * dist;
	lockPos.z += ADJ_[d].z * dist;
}

glm::vec3 Camera::	corner(){
	return glm::vec3 (xPos-32, 0, zPos-12);
}

//********************************* EXTERNAL *********************************

void loop360(float &theta){
	if (theta >= 360) theta -= 360;
	if (theta < 0) theta += 360;
}

glm::vec3 calcThetaV(float theta){
	loop360(theta);
	//get 2d vector of current theta
	glm::vec3 V = glm::vec3(0.0);
	if (theta != 180 && theta != 0) V.x = sin(theta * pi/180);
	if (theta != 90 && theta != 270) V.z = cos(theta * pi/180);
	return V;
	
}

float findTheta(glm::vec3 v){ //V
	float theta = 0;
	if (v.z < 0) 
		theta = (pi + atan(v.x / v.z)) * 180/pi;
	else if (v.z > 0) 
		theta = atan (v.x / v.z) * 180/pi;
	else if (v.z == 0){
		if (v.x > 0) theta = 90;
		else if (v.x < 0) theta = 270;
	}
	loop360(theta);
	return theta;
}



void truncate(glm::vec3 &v, float max){	

	if (glm::length2(v) > max * max){ 		
		v = glm::normalize(v); 
		v *= max;
	}
}


float distSQ(glm::vec3 p1, glm::vec3 p2){
	glm::vec3 v = p1 - p2;
	return glm::length2(v);
}


float getDistSq(glm::vec3 v1, glm::vec3 v2){
	v1 = v1 - v2;
	return v1.x * v1.x + v1.y * v1.y + v1.z * v1.z;
}
long getDistSq2(glm::vec3 v1, glm::vec3 v2){
	v1 = v1 - v2;	
	return v1.x * v1.x + v1.y * v1.y + v1.z * v1.z;
}

bool notZero(glm::vec3 v){
	if(v.x != 0.0) return true;
	if(v.z != 0.0) return true;
	if(v.y != 0.0) return true;
	return false;
}



glm::vec3 radialOffset(glm::vec3 o, float arc, float dist){
	glm::vec3 v;
	float theta = arc;
	v = calcThetaV(theta);
	v *= dist; v += o;
	return v;
}