#ifndef HEALTH_H
#define HEALTH_H

#include "Component.h"


//********************************* CONSTANTS *********************************

//********************************* INITIALIZATION *********************************


class Health: public Component  {
public:
	
	Health::Health()		{	health = 1; maxHealth = 1;	rate = 0;}
	Health::Health(int h)		{	health = h; maxHealth = h;	rate = 0;}

	int Health::update(float delta){ 		
		if (rate){
			health += rate * delta;  	
			if (health <= 0){
				health = 0; rate = 0;
			}else if (health > maxHealth){
				health = maxHealth; rate = 0;
			}
		}
		return health;
	}
	void Health::set(int h){ health = h; maxHealth = h;  }
	void Health::setRate(int r){ rate = r;  }
	bool Health::isDead(){return health <= 0;}
	void Health::kill(){ health = 0;}
	float Health::percent(){ float h = health; return h/maxHealth;}

	int health;
	int maxHealth;
	int rate;
};

#endif