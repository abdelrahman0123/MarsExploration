#pragma once
#include "..\All_Files.h"

class MarsStation
{
	// Lists
	Queue<Event*> Events;
	PriQ<EmergencyMission*> EmergencyMissions;
	Queue<MountainousMission*> MountainousMissions;
	Queue<PolarMission*> PolarMissions;
	PriQ<EmergencyRover*> EmergencyRovers;
	PriQ<MountainousRover*> MountainousRovers;
	PriQ<PolarRover*> PolarRovers;
	PriQ<Mission*> InExecutionMissions;
	PriQ<Rover*> InExecutionRovers;
	PriQ<Rover*> MaintenanceRovers;
	Queue<Mission*> CompletedMissions;
public:
	// Default Constructor
	MarsStation();

	// Add to Lists
	void AddToEmergencyMissions(EmergencyMission* EM, int sig);
	void AddToMountainousMissions(MountainousMission* MM);
	void AddToPolarMissions(PolarMission* PM);
	void AddToEmergencyRovers(EmergencyRover* ER, int speed);
	void AddToMountainousRovers(MountainousRover* MR, int speed);
	void AddToPolarRovers(PolarRover* PR, int speed);
	void AddToInExecutionMissions(Mission* M, int n);
	void AddToInExecutionRovers(Rover* R, int n);
	void AddToMaintenanceRovers(Rover* R, int n);
	void AddToCompletedMissions(Mission* EM);

	// Remove from Lists
	EmergencyMission* RemoveFromEmergencyMissions();
	MountainousMission* RemoveFromMountainousMissions();
	PolarMission* RemoveFromPolarMissions();
	EmergencyRover* RemoveFromEmergencyRovers();
	MountainousRover* RemoveFromMountainousRovers();
	PolarRover* RemoveFromPolarRovers();
	Mission* RemoveFromInExecutionMissions();
	Rover* RemoveFromInExecutionRovers();
	Rover* RemoveFromMaintenanceRovers();
	Mission* RemoveFromCompletedMissions();

	// Cancel Mountainous Mission
	void CancelMountainousMission(Mission* MM);

	// Promote Mountainous Mission
	void PromoteMountainousMission(Mission* MM);

	// Destructor
	~MarsStation();
};

