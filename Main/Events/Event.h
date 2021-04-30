#pragma once
#include "..\MarsStation\MarsStation.h"
#include "..\Missions\Mission.h"
class Event
{
	int EventDay;
	int MissionID;
protected:
	MarsStation* Station;
public:
	Event(int day, int ID);
	void setEventDay(int day);
	int getEventDay();
	void setMissionID(int ID);
	int getMissionID();
	virtual void Execute() = 0;
};

