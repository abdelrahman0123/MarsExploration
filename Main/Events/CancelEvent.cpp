#include "CancelEvent.h"
#include"..\MarsStation\MarsStation.h"

CancelEvent::CancelEvent(MarsStation* MS, int day, int ID) : Event(day, ID, MS)
{
}

void CancelEvent::Execute()
{
	Station->CancelMission(this->getMissionID());
}

CancelEvent::~CancelEvent()
{
}
