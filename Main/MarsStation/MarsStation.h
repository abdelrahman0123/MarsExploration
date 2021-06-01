#pragma once
#include "..\All_Files.h"
#include <fstream>
#include<chrono>
#include <thread>
using namespace std::this_thread; // sleep_for, sleep_until
using namespace std::chrono; // nanoseconds, system_clock, seconds
class MarsStation
{
	//Input and output files
	ifstream ipFile;
	ofstream opFile;
	int AutoPromotionLimit;						//Auto Promotion limit to be set for the whole program
	int ED, ID, TLOC, MissionDur, SIG;			//Numbers associated with the events in the input file
	MissionType Mtype;

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

	UI* UserInterface;
	UI interact;
	int currentDay = 1;

	int roversCount{ 0 }, mountRCount{ 0 }, polarRCount{ 0 }, emrgncyRCount{ 0 }, checkUpCount{ 0 };
	int mountMCount{ 0 }, polarMCount{ 0 }, emrgncyMCount{ 0 }, completedMcount{ 0 };
public:
	// Default Constructor
	MarsStation();
	
	void Simulate();

	//Input file associated functions
	void ReadInput();				//Main input function
	void readRovers();				//Reads the rovers data, create and add them to their waiting list
	void createEventsList();		//Reads the events data, create and add them to their list
	void setMtype(char M);
	MissionType getMtype();

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

	bool CheckWaitingMissions();

	void ExecuteEvent();

	// Assignment
	void AssignEmergencyMission();
	void AssignMountainousMission();
	void AssignPolarMission();

	bool CheckAvailableRover(Rover*& R, char Type);

	void AssignRoverToMission(Rover* R, Mission* M);

	int getAutoP();

	// Cancel Mountainous Mission
	void CancelMission(int ID);

	// Promote Mountainous Mission
	void PromoteMission(int ID);

	void UpdateMissions();
	void HandleMission();
	// Move Rovers
	void MoveRoverFromAvailabeToBusy(Rover*);
	void MoveRoverFromBusyToAvailable();
	void MoveRoverFromBusyToCheckup(Rover*);
	void MoveRoverFromCheckupToAvailable();

	//Output file associated functions
	void PrintOutput();
	char getMissionType(Mission* base);
	void getStatistics();
	void printRoversData();

	template<typename T>
	void ExchangeQueues(Queue<T>& Q1, Queue<T>& Q2);
	void ExchangeEMissions(PriQ<EmergencyMission*>& Q1, PriQ<EmergencyMission*>& Q2);
	void ExchangeExecMissions(PriQ<Mission*>& Q1, PriQ<Mission*>& Q2);

	void simulateInteractive();
	void simulateStepByStep();
	void simulateSilent();
	void simulateG(int x);

	// Destructor
	~MarsStation();
};

template<typename T>
inline void MarsStation::ExchangeQueues(Queue<T>& Q1, Queue<T>& Q2)
{
	T temp;
	while (!Q1.isEmpty())
	{
		Q1.dequeue(temp);
		Q2.enqueue(temp);
	}
}
