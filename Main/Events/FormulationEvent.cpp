#include "FormulationEvent.h"

FormulationEvent::FormulationEvent(Mission* MType, int day, int ID) : Event(day, ID)
{
	MissionType = MType;
}

void FormulationEvent::Execute()
{
	/*
		Mission* Type = dynamic_cast<EmergencyMission> (MissionType);
		if (Type)
		{
			Station->AddToEList(MissionType);
			return;
		}
		Type = dynamic_cast<MountainousMission> (MissionType);
		if (Type)
		{
			Station->AddToMList(MissionType);
			return;
		}
		Station->AddToPList(MissionType);
	*/
}
