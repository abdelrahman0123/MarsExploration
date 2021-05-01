#include "CancelEvent.h"

CancelEvent::CancelEvent(MissionType Type, int day, int ID) : Event(day, ID), MType(Type)
{
}

void CancelEvent::Execute()
{
	
}
