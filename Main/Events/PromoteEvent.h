#pragma once
#include "Event.h"
class PromoteEvent : public Event
{
	MissionType MType;
public:
	PromoteEvent(MissionType Type, int day, int ID);
	virtual void Execute();
};

