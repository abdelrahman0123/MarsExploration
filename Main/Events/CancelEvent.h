#pragma once
#include "Event.h"
class CancelEvent : public Event
{
	MissionType MType;
public:
	CancelEvent(MissionType Type, int day, int ID);
	virtual void Execute();
};

