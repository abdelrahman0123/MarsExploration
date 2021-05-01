#pragma once
#include "Event.h"
class FormulationEvent : public Event
{
	MissionType MType; // Mission Type to be formulated
public:
	FormulationEvent(MissionType Type, int day, int ID);
	virtual void Execute();
};

