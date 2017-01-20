#ifndef SUBOBJ_H
#define SUBOBJ_H

#include "../Components/GridData.h"


class Observer{
public:
	virtual void Observer::onNotify(GridData& data, string msg){}
	virtual void Observer::update() {	}
};


class Subject{
public:	
	Subject::Subject(){observers.reserve(3);}
	void addObserver(Observer* ob) {   observers.push_back(ob);}

	void notify(GridData& data)  {
		ID s = observers.size();
		for (ID i = 0; i < s; i++)    {
			Observer* ob = observers[i];
			ob->onNotify(data, message);
		}
	}

	vector <Observer *> observers;
	string message;
};


#endif