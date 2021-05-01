#pragma once
#include "Event.h"
class PromoteEvent : public Event
{
	Mission* M_Mission; // Mission to be promoted
public:
	PromoteEvent(Mission* M, int day, int ID);
	virtual void Execute();
};

