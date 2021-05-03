#pragma once
#include "Event.h"
class CancelEvent : public Event
{
public:
	// Initializing constructor
	CancelEvent(int day, int ID);
	// Execute
	virtual void Execute();
	// Destructor
	~CancelEvent();
};

