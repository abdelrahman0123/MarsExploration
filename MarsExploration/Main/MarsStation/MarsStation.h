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

	//Events
	Queue<Event*> Events;
	//Missions
	PriQ<EmergencyMission*> EmergencyMissions;
	LinkedList<MountainousMission*> MountainousMissions;
	Queue<PolarMission*> PolarMissions;
	PriQ<Mission*> InExecutionMissions;
	Queue<Mission*> CompletedMissions;
	//Rovers
	PriQ<Rover*> EmergencyRovers;
	PriQ<Rover*> MountainousRovers;
	PriQ<Rover*> PolarRovers;
	PriQ<Rover*> InExecutionRovers;
	PriQ<Rover*> RoversCheckup;

	//UI 
	UI* UserInterface;

	//Current Day
	int currentDay = 1;

	//Counters
	int autoPCount{ 0 }, promotedCount{ 0 };
	int roversCount{ 0 }, mountRCount{ 0 }, polarRCount{ 0 }, emrgncyRCount{ 0 }, checkUpCount{ 0 };
	int mountMCount{ 0 }, polarMCount{ 0 }, emrgncyMCount{ 0 }, completedMcount{ 0 };
	int maxRoversCount{ 0 };
public:
	// Default Constructor
	MarsStation();
	
	//Sim
	void Simulate();
	void simulateInteractive();
	void simulateStepByStep();
	void simulateSilent();
	void simulateG(int x);
	bool NotValid(); //Check if there are Polar missions with no polar rover available
	                 //Or if there is a mountainous mission with no mountainous or emergency rover available
	                 //In this case, missions cant be assigned so we end simulation.

	//Input file associated functions
	void ReadInput(string Input);               //Main input function
	int getmax(int x, int y, int z);
	void readRovers();				//Reads the rovers data, create and add them to their waiting list
	void createEventsList();		//Reads the events data, create and add them to their list
	void setMtype(char M);
	MissionType getMtype();

	//CurrentDay
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

	//Check if waiting missions are all empty or not
	bool CheckWaitingMissions();

	//Execute Events
	void ExecuteEvent();

	// Assignment
	void AssignEmergencyMission();
	void AssignMountainousMission();
	void AssignPolarMission();
	bool CheckAvailableRover(Rover*& R, char Type);
	void AssignRoverToMission(Rover* R, Mission* M);

	//AutoP
	int getAutoP();

	// Cancel Mountainous Mission
	void CancelMission(int ID);

	// Promote Mountainous Mission
	void PromoteMission(int ID);

	//Update Missions
	void UpdateMissions();
	void HandleMission();

	//Move Rovers
	void MoveRoverFromAvailabeToBusy(Rover*);
	void MoveRoverFromBusyToAvailable();
	void MoveRoverFromBusyToCheckup(Rover*);
	void MoveRoverFromCheckupToAvailable();

	//Output file associated functions
	void PrintOutput();
	char getMissionType(Mission* base);
	void getStatistics();
	void printRoversData();

	//Exchange
	template<typename T>
	void ExchangeQueues(Queue<T>& Q1, Queue<T>& Q2);
	void ExchangeEMissions(PriQ<EmergencyMission*>& Q1, PriQ<EmergencyMission*>& Q2);
	void ExchangeExecMissions(PriQ<Mission*>& Q1, PriQ<Mission*>& Q2);
	void ExchangeExecRovers(PriQ<Rover*>& Q1, PriQ<Rover*>& Q2);

	//Print from UI
	void print();

	//Destructor
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
