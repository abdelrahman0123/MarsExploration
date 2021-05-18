#pragma once
#include "..\All_Files.h"

class MarsStation
{
	// Lists
	Queue<Event*> Events;

	PriQ<EmergencyMission*> EmergencyMissions;
	LinkedList<MountainousMission*> MountainousMissions;
	Queue<PolarMission*> PolarMissions;

	PriQ<Mission*> InExecutionMissions;
	Queue<Mission*> CompletedMissions;

	PriQ<Rover*> EmergencyRovers;
	PriQ<Rover*> MountainousRovers;
	PriQ<Rover*> PolarRovers;
	PriQ<Rover*> InExecutionRovers;
	PriQ<Rover*> RoversCheckup;

	UI interact;
	int currentDay = 1;
	int MountMissionsCount = 0;
	int AutoPromotionLimit;
public:
	// Default Constructor
	MarsStation();
	
	void ReadInput();

	void IncrementCurrentDay();
	int getCurrentDay();
	// Add to Lists
	void AddToEvents(Event* newEvent);
	void AddToEmergencyMissions(EmergencyMission* EM, int pri);
	void AddToMountainousMissions(MountainousMission* MM);
	void AddToPolarMissions(PolarMission* PM);
	void AddToEmergencyRovers(Rover* ER, float speed);
	void AddToMountainousRovers(Rover* MR, float speed);
	void AddToPolarRovers(Rover* PR, float speed);
	void AddToInExecutionMissions(Mission* M, int n);
	void AddToInExecutionRovers(Rover* R, int n);
	void AddToRoversCheckup(Rover* R, int n);
	void AddToCompletedMissions(Mission* EM);

	// Remove from Lists
	Event* RemoveFromEvents();
	EmergencyMission* RemoveFromEmergencyMissions();
	MountainousMission* RemoveFromMountainousMissions(int i = 1);
	PolarMission* RemoveFromPolarMissions();
	Rover* RemoveFromEmergencyRovers();
	Rover* RemoveFromMountainousRovers();
	Rover* RemoveFromPolarRovers();
	Mission* RemoveFromInExecutionMissions();
	Rover* RemoveFromInExecutionRovers();
	Rover* RemoveFromRoversCheckup();
	Mission* RemoveFromCompletedMissions();

	// Assignment
	bool AssignEmergencyMission();
	bool AssignMountainousMission();
	bool AssignPolarMission();

	bool CheckAvailableRover(Rover*& R, char Type);

	void AssignRoverToMission(Rover* R, Mission* M);

	// Mountainous Missions Count
	int getMountMissionsCount();
	void IncrementMountMissionsCount();
	void DecrementMountMissionsCount();

	int getAutoP();
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

