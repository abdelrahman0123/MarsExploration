#pragma once
#include "..\MissionType.h"
class MarsStation;
class Event
{
	int EventDay; //Day on which an event should be executed
	int MissionID; //ID of the mission related with the event whether F/C/P
protected:
	MarsStation* Station;
public:
	//Constructor
	Event(int day, int ID, MarsStation* MS);
	//EventDay
	void setEventDay(int day);
	int getEventDay();
	//MissionID
	void setMissionID(int ID);
	int getMissionID();
	//Execute
	virtual void Execute() = 0;
	//Destructor
	virtual ~Event();
};

