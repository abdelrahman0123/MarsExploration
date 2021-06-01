#include "FormulationEvent.h"
#include"..\MarsStation\MarsStation.h"

FormulationEvent::FormulationEvent(MarsStation* MS, MissionType Type, int day, int ID, int loc, int dur, int sig) : Event(day, ID, MS), MType(Type)
{
	TLOC = loc;
	MDUR = dur;
	SIG = sig;
}

void FormulationEvent::Execute()
{
	if (MType == Emergency)
	{
		EmergencyMission* EM = new EmergencyMission(this->getMissionID(), TLOC, MDUR, SIG, this->getEventDay()); // Create new emergency mission
		Station->AddToEmergencyMissions(EM, EM->GetPriority()); // Add it to the list
		return;
	}
	else if (MType == Mountainous)
	{
		MountainousMission* MM = new MountainousMission(this->getMissionID(), TLOC, MDUR, SIG, this->getEventDay(), Station->getAutoP()); // Create new mountainous mission
		Station->AddToMountainousMissions(MM); // Add it to the list
		return;
	}
	// Mission type is polar
	PolarMission* PM = new PolarMission(this->getMissionID(), TLOC, MDUR, SIG, this->getEventDay()); // Create new polar mission
	Station->AddToPolarMissions(PM); // Add it to the list
}

FormulationEvent::~FormulationEvent()
{
}
