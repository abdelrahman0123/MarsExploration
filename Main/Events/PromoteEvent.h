#pragma once
#include "Event.h"
class PromoteEvent : public Event
{
	Mission* M_Mission;
public:
	PromoteEvent(Mission* M, int day, int ID);
	virtual void Execute();
};

