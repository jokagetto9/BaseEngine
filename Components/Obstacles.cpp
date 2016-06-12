//********************************* INITIALIZATION *********************************
#include "Obstacles.h"


SizeProfile * Obstacles::sizeP = NULL;
vector<SizeProfile>  Obstacles::sizeProfiles;

Obstacles::Obstacles(){		
	ob.resize(4, glm::vec3(0));
	obDist.resize(4, FURTHEST);
	furthest = FURTHEST;
	count = 0;
}

Obstacles::Obstacles(ID max){
	ob.resize(max, glm::vec3(0));
}


void Obstacles::clear(){
	for (ID i = 0; i < count; i++){
		ob[i] = glm::vec3(0);
		obDist[i] = FURTHEST;
	}
	count = 0;
	furthest = FURTHEST;
	sizeP = &sizeProfiles[0];
}
//********************************* NEIGHBOURS *********************************

void Obstacles::testObject(glm::vec3 pos, float d){
	ID s = ob.size();
	if (count < s){
		for (ID c = 0; c < s; c++){
			if (d < obDist[c] ){
				addObject(count, pos, d);
				if (count)
					shuffle(c, count);
				count++;
			}
		}
	}else if (d < furthest) {		
		addObject(s-1, pos, d);
		furthest = d;
		shuffle(0, s-1);
	}
}


void Obstacles::shuffle(ID i1, ID i2){
	ID index = i2;
	for (int i = i2-1; i >= i1 && i >= 0; i--){
		if (obDist[index] < obDist[i]){
			swap(index, i);
			index--;
		}else{
			i = i1-1;
		}
	}
	furthest = obDist[count-1];
}
void Obstacles::addObject(ID i, glm::vec3 pos, float d){
	ob[i] = pos;
	obDist[i] = d;
}



void Obstacles::updateObDist(glm::vec3 pos){
	for (int i = 0; i < count; i++){
		if (!obDist[i])
			obDist[i] = getDistSq(ob[i], pos);
	}
}



glm::vec3 Obstacles::calcAlign(){
	glm::vec3 align; align = glm::vec3(0.0);
	float d;
	for (int i = 0; i < count; i++){
			d = obDist[i];
			float c = (GROUP_RANGE - d)/ GROUP_RANGE;
			//align += motion[i]->speed * c;
	}
	return align;
}

glm::vec3 Obstacles::calcSep(glm::vec3 pos){
	if (count){
		glm::vec3 sep; sep = glm::vec3(0.0);
		glm::vec3 dv; float d;
		for (int i = 0; i < count; i++){
			dv = pos - ob[i];
			d = sqrt(obDist[i]);
			if (d <= sizeP->sepRad){
				float c = (sizeP->sepRad - d/2)/ sizeP->sepRad;
				sep += c * dv/d;
			}
		}
		return sep;
	}else 
		return glm::vec3(0.0);
}


glm::vec3 Obstacles::calcCoh(glm::vec3 pos){
	glm::vec3 coh; coh = glm::vec3(0.0);
	glm::vec3 dv; float d;
	for (int i = 0; i < count; i++){
		dv = ob[i] - pos;
		d = sqrt(obDist[i]);
		if (d > sizeP->sepRad){			
			float c = (sizeP->cohRad - d)/ sizeP->cohRad; //d/GROUP_RANGE;
			coh += c * dv/d; 
		}
	}
	return coh;
}

bool Obstacles::collide(glm::vec3 pos){
	if (count){
		glm::vec3 sep; sep = glm::vec3(0.0);
		glm::vec3 dv; float d;
		for (int i = 0; i < count; i++){
			dv = pos - ob[i]; 
			d = obDist[i];
			if (d <= sizeP->crashRad){
				return true;
			}
		}
	}else 
		return false;
}

void Obstacles::swap(ID i1, ID i2){
	glm::vec3 v = ob[i1];
	float f = obDist[i1];
	ob[i1] = ob[i2];
	obDist[i1] = obDist[i2];
	ob[i2] = v;
	obDist[i2] = f;
}

/*/
void Obstacles::findSchool(NPC *null, int nullCount){
	int friends = 0;
	for (int i = 0; i < nullCount || friends == GROUP_MIN; i++){
		if (getDistanceSQ(null[i].pos()))	friends ++;
	}	
	if (friends == GROUP_MIN) halt();
	else randomDirection();
	



void Obstacles::aiUpdate(float aiDelta, float slowai){
	int friends = 0;
	int slimeChecked = 0;
	int slimeToCheck = ceil(slowai*(slimeCount-slimeCaught));
	while (slimeChecked < slimeToCheck){
		if (slime[nextSlime].caught){
			//cycle through slime thoughts
			if (nextSlime+1 >= slimeCount) nextSlime = 0;
			else nextSlime++;	
		}else{
			for (int j = 0; j < slimeCount && friends != SCHOOL_MIN; j++){
				if (j != nextSlime){
					if (slime[nextSlime].checkDistance(slime[j])) friends++;
				}
			}	
			if (friends == SCHOOL_MIN) slime[nextSlime].stop();
			else slime[nextSlime].changeDirection();
			if (nextSlime == slimeCount-1) f.changeDirection(); 

			//cycle through slime thoughts
			if (nextSlime+1 == slimeCount) nextSlime = 0;
			else nextSlime++;
			slimeChecked++;
		}
	}
}

}//*/