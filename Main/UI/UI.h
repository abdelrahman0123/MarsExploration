#include <iostream>
#include <fstream>
#include "..\DataStructures\Queue.h"
#include "../MissionType.h"
#include "../EventType.h"
using namespace std;
#pragma once
class UI
{
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

};

