#include "PromoteEvent.h"

PromoteEvent::PromoteEvent(Mission* M, int day, int ID) : Event(day, ID)
{
	M_Mission = dynamic_cast<MountainousMission*> (M);
}

void PromoteEvent::Execute()
{
	if (M_Mission)
		Station->PromoteMountainousMission(M_Mission);
}
