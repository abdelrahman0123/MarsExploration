#pragma once
#include "Event.h"
class PromoteEvent : public Event
{
public:
	// Initializing Constructor
	PromoteEvent(MarsStation* MS, int day, int ID);
	// Execute
	virtual void Execute();
	// Destructor
	~PromoteEvent();
};

