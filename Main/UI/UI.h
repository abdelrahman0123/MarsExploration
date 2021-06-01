#pragma once
#include<iostream>
#include "..\All_Files.h"
using namespace std;
class UI {


public:
	UI();
	char selectMode();
	bool interactiveMode();
	void stepByStepMode();
	void silentMode();
	void printCurrentDay(int day);
	void printWaitingMissions(PriQ<EmergencyMission*> emrgncy, LinkedList<MountainousMission*> mount, Queue<PolarMission*> polar, int E, int M, int P);
	void printInExecution(PriQ<Mission*> missions);
	void printAvailableRovers(int availableRvrs, PriQ<Rover*> emrgncy, PriQ<Rover*> mount, PriQ<Rover*> polar);
	void printInCheckup(int checkup, PriQ<Rover*> rovers);
	void printCompletedMissions(int completedCount, Queue<Mission*> Completed);

};