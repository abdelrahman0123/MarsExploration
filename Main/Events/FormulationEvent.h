#pragma once
#include "Event.h"
class FormulationEvent : public Event
{
	Mission* MissionType; // Mission to be formulated
public:
	FormulationEvent(Mission* MType, int day, int ID);
	virtual void Execute();
};

