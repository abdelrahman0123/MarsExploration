#include "FormulationEvent.h"

FormulationEvent::FormulationEvent(MissionType Type, int day, int ID) : Event(day, ID), MType(Type)
{
}

void FormulationEvent::Execute()
{
	if (MType == Emergency)
	{
		EmergencyMission* EM = new EmergencyMission();
		Station->AddToEmergencyMissions(EM, sig);
		return;
	}
	else if (MType == Mountainous)
	{
		MountainousMission* MM = new MountainousMission();
		Station->AddToMountainousMissions(MM);
		return;
	}
	PolarMission* PM = new PolarMission();
	Station->AddToPolarMissions(PM);
}
