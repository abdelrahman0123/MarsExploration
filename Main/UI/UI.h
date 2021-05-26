#include <iostream>
#include <fstream>
#include "..\DataStructures\Queue.h"
#include "../MissionType.h"
#include "../EventType.h"
using namespace std;
#pragma once
#include"../DataStructures/Queue.h"
class UI{
/*
private:
	ifstream ipFile;
	ofstream opFile;

	Queue<int>* emergencyRovers;
	Queue<int>* polarRovers;
	Queue<int>* mountRovers;

	Queue<int>* eventData;

	MissionType MT;
	EventType ET;
public:
	UI();
	void readRovers();
	int getAutoP();		//Getting the auto promotion limit
	int getNumofEvents();
	Queue<int>* getEvent();
	~UI();

	//Getters for rovers data
	Queue<int>* getEmRovers();
	Queue<int>* getPolarRovers();
	Queue<int>* getMountRovers();

	void setEtype(char E);
	EventType getET();
	
	void setMtype(char M);
	MissionType getMT();
	//Event data getter
	//Queue<int>* getEventData();
	*/
	int avPolarRoversnum =0, avEmergencyRoversnum  = 0, avMountainounsRoversnum  = 0,
		checkupPolarRoversnum  = 0, checkupEmergencyRoversnum =0, checkupMountainousRoversnum =0,
		waitingPolarMissionsnum =0, waitingEmergemcyMissionsnum =0, waitingMountainousMissionsnum =0,
		inExecutionPolarMissionsnum =0, inExecutionMountainousMissionsnum =0, inExecutiomEmergencyMissionsnum =0,
		compPolarMissionsnum =0, compEmergencyMissionsnum =0, comMountainousMissionsnum =0
		, polarCheckupnum =0, emergencyCheckupnum =0, mountainousCheckupnum =0;

	Queue<int> avPolar, avEmergency, avMountainous;
	Queue<int> checkupPolar, checkupEmemergnecy, checkupMountainous, waitingMissionsPolar, waitingMissionsEmergency;
	Queue<int> waitingMissionsMountainous, inExecutionPolar, inExecutionEmergency, inExecutionMountainous;
	Queue<int> completedPolarMissions, completedEmergencyMisisons, completedMountainousMissions;

public:
	UI();
	UI(int p, int em, int m);
	/*void setPolarRoversNum(int n);
	void setEmergencyRoversNum(int n);
	void setMountainousRoversNum(int n);
	void setPolarList(int*pList);
	void setEmergencyList(int* sList);
	void setMountainousList(int* mList);
	void setPolarCheckupList(int* pList);
	void setEmergencyCheckupList(int* emList);
	void setMountainousCheckupList(int* mList);
	int getPolarRoversNum();
	int getEmergencyRoversNum();
	int getMountainousRoversNum();
	//printing
	void print();
	void printWaintingMissions();
	void printInExecutionMissions();
	void printAvailabeRovers();
	void printInCheckupRovers();
	void printCompletedMissions();*/
	void addAvPolar(int n);
	void addAvEmergency(int n);
	void addAvMountainous(int n);
	void addCheckupPolar(int n);
	void addCheckupEmemergnecy(int n);
	void addCheckupMountainous(int n);
	void addWaitingMissionsPolar(int n);
	void addWaitingMissionsEmergency(int n);
	void addWaitingMissionsMountainous(int n);
	void addInExecutionPolar(int n);
	void addInExecutionEmergency(int n);
	void addInExecutionMountainous(int n);
	void addCompletedPolarMissions(int n);
	void addCompletedEmergencyMisisons(int n);
	void addCompletedMountainousMissions(int n);
	void removeAvPolar(  );
	void removeAvEmergency(  );
	void removeAvMountainous(  );
	void removeCheckupPolar(  );
	void removeCheckupEmemergnecy(  );
	void removeCheckupMountainous(  );
	void removeWaitingMissionsPolar(  );
	void removeWaitingMissionsEmergency(  );
	void removeWaitingMissionsMountainous(  );
	void removeInExecutionPolar(  );
	void removeInExecutionEmergency(  );
	void removeInExecutionMountainous(  );
	void removeCompletedPolarMissions(  );
	void removeCompletedEmergencyMisisons(  );
	void removeCompletedMountainousMissions(  );


};

