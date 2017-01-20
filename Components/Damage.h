#ifndef DAMAGE_H
#define DAMAGE_H

#include "Component.h"


//********************************* CONSTANTS *********************************

//********************************* INITIALIZATION *********************************


class Damage{
public:
	Damage::Damage(){damage = 0;}

	Damage::Damage(int dmg){damage = dmg;}

	int damage;
	

};

#endif