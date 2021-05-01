#pragma once
#include<iostream>
using namespace std;
#include"..\Missions\Mission.h"
class Rover
{
	char roverType;
	int checkUpDuration;
	int speed;
	Mission* assignedMission;
	string status;
public:
	Rover();
	Rover(char r, int c, int s,Mission* m, string st);
	void setRoverType(char t);
	void setCheckUpDuration(int d);
	void setRoverSpeed(int s);
	void setAssignedMission(Mission *);
	void setStatus(string st);
	char getRoverType();
	int getCheckUpDuration();
	int getRoverSpeed();
	Mission* getAssignedMission();
	bool getStatus();
	void operator =(const Rover& r);
	~Rover();

};

