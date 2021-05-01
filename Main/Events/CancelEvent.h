#pragma once
#include "Event.h"
class CancelEvent : public Event
{
	Mission* M_Mission; // Mission to be cancelled
public:
	CancelEvent(Mission* M, int day, int ID);
	virtual void Execute();
};

