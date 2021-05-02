#include "CancelEvent.h"

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
