//********************************* INITIALIZATION *********************************
#include "Obstacles.h"


SizeProfile Obstacles::ignore = {0, 0, 0, 0, 0};
SizeProfile & Obstacles::sizeP = ignore;
vector<SizeProfile>  Obstacles::sizeProfiles;

Obstacles::Obstacles(){		
	ob.resize(4, glm::vec3(0));
	obDist.resize(4, FURTHEST);
	obSize.resize(4, 0);
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
	sizeP = sizeProfiles[0];
}
//********************************* NEIGHBOURS *********************************

void Obstacles::applyProfile(ID id){
	assert (id < sizeProfiles.size());
	sizeP = sizeProfiles[id];
}

void Obstacles::testObject(glm::vec3 pos, Ob &o){
	applyProfile(o.sizeP);
	o.d = sqrt(getDistSq(pos, o.pos))-sizeP.baseRad;
	if (o.d > 0 && o.d < sizeP.cohRad) {
		ID s = ob.size();
		if (count < s){
			for (ID c = 0; c < s; c++){
				if (o.d < obDist[c] ){
					addObject(count, o);
					if (count)
						shuffle(c, count);
					count++;
				}
			}
		}else if (o.d < furthest) {		
			addObject(s-1, o);
			furthest = o.d;
			shuffle(0, s-1);
		}
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
void Obstacles::addObject(ID i, Ob &o){
	ob[i] = o.pos;
	obDist[i] = o.d;
	obSize[i] = o.sizeP;
}



void Obstacles::updateObDist(glm::vec3 pos){
	for (int i = 0; i < count; i++){
		if (!obDist[i])
			obDist[i] = sqrt(getDistSq(ob[i], pos));
	}
}



glm::vec3 Obstacles::calcAlign(){
	glm::vec3 align; align = glm::vec3(0.0);
	float d;
	for (int i = 0; i < count; i++){
			d = obDist[i];
			float c = (sizeP.cohRad - d)/ sizeP.cohRad;
			//align += motion[i]->speed * c;
	}
	return align;
}

glm::vec3 Obstacles::calcSep(glm::vec3 pos){
	if (count){
		glm::vec3 sep; sep = glm::vec3(0.0);
		glm::vec3 dv; float d;
		for (int i = 0; i < count; i++){
			d = obDist[i];
			applyProfile(obSize[i]);
			dv = pos - ob[i];
			dv *= d/(d+sizeP.baseRad); 
			if (d <= sizeP.sepRad){
				float c = (sizeP.sepRad - d)/ sizeP.sepRad;
				sep += c * dv/d;
			}
		}
		truncate(sep, sizeP.sepWt);
		return sep;
	}else 
		return glm::vec3(0.0);
}


glm::vec3 Obstacles::calcCoh(glm::vec3 pos){
	glm::vec3 coh; coh = glm::vec3(0.0);
	glm::vec3 dv; float d;
	for (int i = 0; i < count; i++){
		applyProfile(obSize[i]);
		d = obDist[i];
		dv = ob[i] - pos;
		dv *= d/(d+sizeP.baseRad); 
		if (d > sizeP.sepRad){			
			float c = (sizeP.cohRad - d)/ sizeP.cohRad; //d/GROUP_RANGE;
			coh += c * dv/d; 
		}
	}
	truncate(coh, sizeP.cohWt);
	return coh;
}

bool Obstacles::collide(glm::vec3 pos){
	if (count){
		glm::vec3 sep; sep = glm::vec3(0.0);
		glm::vec3 dv; float d;
		for (int i = 0; i < count; i++){			
			applyProfile(obSize[i]);
			dv = pos - ob[i]; 
			d = obDist[i];
			if (d <= sizeP.crashRad){
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