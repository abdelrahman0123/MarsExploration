#pragma once
#include "Event.h"
class FormulationEvent : public Event
{
	MissionType MType; // Mission to be formulated // char
public:
	FormulationEvent(MissionType Type, int day, int ID);
	virtual void Execute();
};

