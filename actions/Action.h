#ifndef ACTION_H
#define ACTION_H

#include "../Area.h"

class Action
{
public:
	Action();

	virtual Area* DoAction() = 0;
};
#endif
