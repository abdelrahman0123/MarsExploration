#pragma once
#include "..\All_Files.h"

class MarsStation
{
	// Lists
	Queue<Event*> Events;
	///
	PriQ<EmergencyMission*> EmergencyMissions;
	Queue<MountainousMission*> MountainousMissions;
	Queue<PolarMission*> PolarMissions;

	PriQ<Mission*> InExecutionMissions;
	Queue<Mission*> CompletedMissions;

	//////
	PriQ<Rover*> EmergencyRovers;
	PriQ<Rover*> MountainousRovers;
	PriQ<Rover*> PolarRovers;

	PriQ<Rover*> InExecutionRovers;
	PriQ<Rover*> RoversCheckup;

	int currentDay = 1;
	
public:
	// Default Constructor
	MarsStation();
	
	void IncrementCurrentDay();
	int getCurrentDay();
	// Add to Lists
	void AddToEmergencyMissions(EmergencyMission* EM, int sig);
	void AddToMountainousMissions(MountainousMission* MM);
	void AddToPolarMissions(PolarMission* PM);
	void AddToEmergencyRovers(Rover* ER, int speed);
	void AddToMountainousRovers(Rover* MR, int speed);
	void AddToPolarRovers(Rover* PR, int speed);
	void AddToInExecutionMissions(Mission* M, int n);
	void AddToInExecutionRovers(Rover* R, int n);//not needed
	void AddToRoversCheckup(Rover* R, int n);//not needed
	void AddToCompletedMissions(Mission* EM);

	// Remove from Lists
	EmergencyMission* RemoveFromEmergencyMissions();
	MountainousMission* RemoveFromMountainousMissions();
	PolarMission* RemoveFromPolarMissions();
	Rover* RemoveFromEmergencyRovers();//not needed
	Rover* RemoveFromMountainousRovers();//not needed
	Rover* RemoveFromPolarRovers();//not needed
	Mission* RemoveFromInExecutionMissions();
	Rover* RemoveFromInExecutionRovers();
	Rover* RemoveFromRoversCheckup();
	Mission* RemoveFromCompletedMissions();

	// Cancel Mountainous Mission
	void CancelMission(int ID);

	// Promote Mountainous Mission
	void PromoteMission(int ID);

	void UpdateMissions();
	void HandleMission();

	void MoveRoverFromAvailabeToBusy(Rover*);
	void MoveRoverFromBusyToAvailable();
	void MoveRoverFromAvailableToCheckup(Rover*);
	void MoveRoverFromCheckupToAvailable();
	// Destructor
	~MarsStation();
};

