#pragma once
#include "Event.h"
class FormulationEvent : public Event
{
	MissionType MType; // Mission Type to be formulated
	int TLOC; // Target Location
	int MDUR; // Mission Duration
	int SIG; // Significance
public:
	// Initializing constructor
	FormulationEvent(MissionType Type, int day, int ID, int loc, int dur, int sig);
	// Execute
	virtual void Execute();
	// Destructor
	~FormulationEvent();
};

