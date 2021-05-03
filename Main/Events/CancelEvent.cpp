#include "CancelEvent.h"
#include"..\MarsStation\MarsStation.h"

CancelEvent::CancelEvent(int day, int ID) : Event(day, ID)
{
}

void CancelEvent::Execute()
{
	Station->CancelMission(this->getMissionID());
}

CancelEvent::~CancelEvent()
{
}
