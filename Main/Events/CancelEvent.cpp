#include "CancelEvent.h"

CancelEvent::CancelEvent(Mission* M, int day, int ID) : Event(day, ID)
{
	M_Mission = dynamic_cast<MountainousMission*> (M);
}

void CancelEvent::Execute()
{
	/*
	if (M_Mission)
		Station->CancelMountainous(M_Mission);
	*/
}
