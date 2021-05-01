#pragma once
#include "..\All_Files.h"
class MarsStation
{
	// Lists
	Queue<Event> Events;
	PriQ<EmergencyMission> EmergencyMissions;
	Queue<Event> MountainousMissions;
	Queue<Event> PolarMissions;
	PriQ<Event> EmergencyRovers;
	PriQ<Event> MountainousRovers;
	PriQ<Event> PolarRovers;
	PriQ<Event> InExecutionMissions;
	PriQ<Event> InExecutionRovers;
	PriQ<Event> MaintenanceRovers;
	Queue<Mission> CompletedMissions; // 3adel el types
public:
	MarsStation();
};

