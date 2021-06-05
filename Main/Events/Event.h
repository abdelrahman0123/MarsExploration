#pragma once
#include "..\MissionType.h"
class MarsStation;
class Event
{
	int EventDay;
	int MissionID;
protected:
	MarsStation* Station;
public:
	Event(int day, int ID, MarsStation* MS);
	void setEventDay(int day);
	int getEventDay();
	void setMissionID(int ID);
	int getMissionID();
	virtual void Execute() = 0;
	virtual ~Event();
};

